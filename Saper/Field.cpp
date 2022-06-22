
#include "Field.h"
#include "Globals.h"
#include "Cell.h"
#include <SFML/Graphics.hpp>
#include <vector>


using namespace sf;

Field::Field(){
    for (int row=0; row<ROWS; row++){
        for (int column=0; column<COLUMNS; column++){
            cells.push_back(Cell(column, row));
        }
    }
    reset();
}

void Field::reset() {
    game_over = false;
    first_click = true;
    for (Cell &cell : cells){
        cell.reset();
    }
}

void Field::draw(RenderWindow& window) {
    RectangleShape cell_shape(Vector2f(CELL_SIZE-1, CELL_SIZE-1));
    Sprite sprite;
    Texture texture;
    texture.loadFromFile("../tiles.jpg");
    sprite.setTexture(texture);


    for (int row=0; row<ROWS; row++){
        for (int column=0; column<COLUMNS; column++){
            cell_shape.setPosition(column*CELL_SIZE, row*CELL_SIZE);
            Cell* current_cell = get_cell(column, row);

            if (game_over && current_cell->is_mine()){
                sprite.setPosition(column*CELL_SIZE, row*CELL_SIZE);
                sprite.setTextureRect(sf::IntRect(CELL_SIZE * 9, 0, CELL_SIZE, CELL_SIZE));

                window.draw(sprite);
            }
            else if (current_cell->is_hiden()){
                sprite.setPosition(column*CELL_SIZE, row*CELL_SIZE);
                sprite.setTextureRect(sf::IntRect(CELL_SIZE*10, 0, CELL_SIZE, CELL_SIZE));

                window.draw(sprite);

                if (current_cell->is_flag()){
                    sprite.setPosition(column*CELL_SIZE, row*CELL_SIZE);
                    sprite.setTextureRect(sf::IntRect(CELL_SIZE * 11, 0, CELL_SIZE, CELL_SIZE));

                    window.draw(sprite);
                }
            }
            else{
                int mines_around = current_cell->get_mines_around();

                cell_shape.setFillColor(sf::Color(146, 182, 255));
                window.draw(cell_shape);

                if (current_cell->is_mine()){
                    cell_shape.setFillColor(sf::Color(255, 0, 0));
                    window.draw(cell_shape);

//                    sprite.setPosition(column*CELL_SIZE, row*CELL_SIZE);
//                    sprite.setTextureRect(sf::IntRect(CELL_SIZE * 9, 0, CELL_SIZE, CELL_SIZE));
//
//                    window.draw(sprite);
                }
                else if (0 <= mines_around)
                {
                    sprite.setPosition(column*CELL_SIZE, row*CELL_SIZE);
                    sprite.setTextureRect(sf::IntRect(CELL_SIZE * mines_around, 0, CELL_SIZE, CELL_SIZE));

                    window.draw(sprite);
                }
            }
            current_cell->set_mouse_state(0);
        }
    }
}

Cell *Field::get_cell(int x, int y) {
    return &cells[COLUMNS * y + x];
}

void Field::flag_cell(int x, int y) {
    if (get_cell(x, y)->is_flag())
        get_cell(x, y)->set_flag(false);
    else
        get_cell(x, y)->set_flag(true);

}

void Field::open_cell(int x, int y) {
    int row, column;
    srand(time(NULL));
    if (first_click){
        for (int i=0; i<MINES; i++){
            row = rand()%ROWS;
            column = rand()%COLUMNS;
            Cell* cur_cell = get_cell(column, row);
            if (cur_cell->is_mine() || (row == y && column == x)){
                i--;
            }
            else {
                cur_cell->set_mine(true);
            }
        }

        for (int r=0; r<ROWS; r++){
            for (int c=0; c<COLUMNS; c++){
                int number = get_mines_around(c, r);
                get_cell(c, r)->set_mines_around(number);
            }
        }
        first_click = false;
    }

    Cell* current_cell = get_cell(x, y);
    if (not current_cell->is_flag() && not game_over){
        current_cell->open(cells);
        if (current_cell->is_mine()){
            game_over = true;
            printf("GAME OVER!\n");
        }
    }


}

int Field::get_mines_around(int x, int y) {
    int near_mines = 0;
    for (int k=0; k<3; k++){
        for (int l=0; l<3; l++){
            if (x-1+l < 0 || x-1+l >= ROWS) continue;
            if (y-1+k  < 0 || y-1+k  >= COLUMNS) continue;
            if (x-1+l == x && y-1+k == y) continue;

            if (get_cell(x-1+l, y-1+k)->is_mine())
                near_mines++;
        }
    }
    return near_mines;
}

bool Field::is_win() {
    for (Cell &cell : cells){
        if (cell.is_hiden() and !cell.is_mine()){
            return false;
        }
    }
    return true;
}


