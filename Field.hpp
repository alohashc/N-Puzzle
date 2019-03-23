//
// Created by aloha on 21.03.19.
//

#ifndef ALOHA_PUZZLE_FIELD_HPP
#define ALOHA_PUZZLE_FIELD_HPP

#include "NPuzzle.hpp"
#include <set>

class Field {
public:
    Field();
    ~Field();

    void    init(int, int);
    void    addTile(int, int);

    void print_tiles();

private:
    int     filed_size;
    int     field_rows;
    int     *target;
    int     gap;
    s_tile* tiles;
};


#endif //ALOHA_PUZZLE_FIELD_HPP
