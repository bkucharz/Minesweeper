#ifndef SAPER_FIELD_H
#define SAPER_FIELD_H
#pragma once


#include <vector>
#include "Cell.h"
#include <SFML/Graphics.hpp>


class Field{
    bool first_click;
    bool game_over;
    std :: vector<Cell> cells;

public:
    Field();
    void reset();
    void draw(sf::RenderWindow& window);
    void flag_cell(int x, int y);
    void open_cell(int x, int y);
    void set_mouse_state(int mouse_state, int x, int y);
    Cell* get_cell(int x, int y);
    int get_mines_around(int x, int y);
    bool is_game_over() { return game_over;};
    bool is_win();
};

#endif SAPER_FIELD_H
