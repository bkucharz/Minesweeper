#include "Cell.h"
#include "Globals.h"
#include <vector>


Cell::Cell(int _x, int _y) {
    mines_around = 0;
    x = _x;
    y = _y;
}

bool Cell::is_flag() {
    return flag;
}

bool Cell::is_mine() {
    return mine;
}

bool Cell::is_hiden() {
    return hiden;
}

void Cell::reset() {
    mine = false;
    flag = false;
    hiden = true;
    mouse_state = 0;
}

void Cell::set_mines_around(int number) {
    mines_around = number;
}

void Cell::set_flag(bool new_flag) {
    flag = new_flag;
}

void Cell::set_mine(bool new_mine) {
    mine = new_mine;
}

void Cell::set_mouse_state(int new_mouse_state) {
    mouse_state = new_mouse_state;
}

bool Cell::open(std::vector<Cell>& cells) {
    if (hiden){
        hiden = false;

        if (not is_mine() and mines_around == 0){
            for (int k=0; k<3; k++){
                for (int l=0; l<3; l++){
                    if (x-1+l < 0 || x-1+l >= COLUMNS) continue;
                    if (y-1+k  < 0 || y-1+k  >= ROWS) continue;
                    if (x-1+l == x && y-1+k == y) continue;


                    if (not cells[COLUMNS*(y-1+k) + (x-1+l)].is_mine())
                        cells[COLUMNS*(y-1+k) + (x-1+l)].open(cells);
                }
            }
        }

    }
    return true;
}

int Cell::get_mines_around() {
    return mines_around;
}




