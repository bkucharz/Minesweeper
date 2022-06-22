#ifndef SAPER_CELL_H
#define SAPER_CELL_H

//#include "Field.h"
#pragma once

#include <vector>

class Cell{
    bool mine;
    bool hiden;
    bool flag;
    int mines_around ;

    int mouse_state;
    int x;
    int y;

public:
    Cell(int _x, int _y);
    bool is_flag();
    bool is_mine();
    bool is_hiden();

    bool open(std::vector<Cell>& i_cells);
    void set_mines_around(int number);
    void set_flag(bool new_flag);
    void set_mine(bool new_mine);
    void set_mouse_state(int new_mouse_state);
    int get_mines_around();
    void reset();

};

#endif //SAPER_CELL_H
