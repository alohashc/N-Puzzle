//
// Created by aloha on 21.03.19.
//

#ifndef ALOHA_PUZZLE_FIELD_HPP
#define ALOHA_PUZZLE_FIELD_HPP

#include "NPuzzle.hpp"

class Field {
public:
    Field();
    ~Field();

    void    init();
    void    addTile();

private:
    int     filed_size;
    int     field_rows;
    int     *target;
    int     gap_pos;
    s_tile* tiles;
};


#endif //ALOHA_PUZZLE_FIELD_HPP
