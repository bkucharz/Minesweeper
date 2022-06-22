#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Globals.h"
#include "Field.h"


using namespace sf;


int main() {
    Event event;
    RenderWindow window(VideoMode(CELL_SIZE*COLUMNS*SCREEN_RESIZE, CELL_SIZE*ROWS*SCREEN_RESIZE), "Saper");
    Field field;



    Text text;
    Font font;
    if (!font.loadFromFile("../AbyssinicaSIL-R.ttf")){
        std::cout<<"Cannot load font"<<std::endl;
        return 1;
    }
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(Color::Black);
    text.setString("SAPER");
    text.setStyle(Text::Bold);
    text.setPosition(CELL_SIZE*COLUMNS/2-50, 50);
    Text t2;
    t2.setFont(font);
    t2.setCharacterSize(10);
    t2.setFillColor(Color::Black);
    t2.setString("Gra polega na wyczyszczeniu pola minowego\n"
                 "Liczba na polu wskazuje liczbe min w poblizu pola\n"
                 "Sterowanie odbywa sie za pomoca myszy:\n"
                 "\t-LPM: odkrycie pola\n"
                 "\t-PPM: Postawienie/Zwiniecie flagi\n\n"
                 "Nacisnij ENTER aby rozpoczac gre");
    t2.setStyle(Text::Bold);
    t2.setPosition(50, 100);
    window.clear(Color(169,169,169));
    window.draw(text);
    window.draw(t2);
    window.display();

    bool quit = false;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyReleased){
                if (event.key.code == Keyboard::Enter){
                    quit = true;
                }
            }
        }
        if (quit) break;
    }


    while (window.isOpen()){
        unsigned char mouse_cell_x = std::clamp(static_cast<int>(floor(sf::Mouse::getPosition(window).x / static_cast<float>(CELL_SIZE * SCREEN_RESIZE))), 0, COLUMNS - 1);
        unsigned char mouse_cell_y = std::clamp(static_cast<int>(floor(sf::Mouse::getPosition(window).y / static_cast<float>(CELL_SIZE * SCREEN_RESIZE))), 0, ROWS - 1);


        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonReleased){
                if (event.mouseButton.button == Mouse::Left)
                    field.open_cell(mouse_cell_x, mouse_cell_y);
                else if (event.mouseButton.button == Mouse::Right){
                    field.flag_cell(mouse_cell_x, mouse_cell_y);
                }
            }

            if (event.type == Event::KeyReleased){
                if (event.key.code == Keyboard::Enter){
                    field.reset();
                }
            }
        }

        window.clear(Color::White);
        field.draw(window);


        if (field.is_game_over()){
            Text t2;
            t2.setFont(font);
            t2.setCharacterSize(20);
            t2.setFillColor(Color::Red);
            t2.setString("\tGAME\n\tOVER\n\nPRESS ENTER");
            t2.setStyle(Text::Bold);
            t2.setPosition(CELL_SIZE * COLUMNS / 2 - 70, 100);
//            window.clear(Color(169,169,169));
            window.draw(t2);
        }
        else if(field.is_win()){
            window.display();
            Time t = seconds(1);
            sleep(t);
            Text t2;
            t2.setFont(font);
            t2.setCharacterSize(20);
            t2.setFillColor(Color::White);
            t2.setString("\tCONGRATULATIONS\n\t\t\tWIN\n\n\t\tPRESS ENTER");
            t2.setStyle(Text::Bold);
            t2.setPosition(CELL_SIZE * COLUMNS / 2 - 130, 100);
            window.clear(Color::Green);
            window.draw(t2);
            window.display();
            quit = false;

            while (true){


                while (window.pollEvent(event))
                {
                    if (event.type == Event::Closed){
                        window.close();
                        quit = true;
                        break;
                    }

                    if (event.type == Event::KeyReleased){
                        if (event.key.code == Keyboard::Enter){
                            field.reset();
                            quit = true;
                            break;
                        }
                    }
                }
                if (quit) break;
            }

        }

        window.display();

    }

    return 0;
}
