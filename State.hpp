//
// Created by aloha on 18.03.19.
//

#ifndef ALOHA_PUZZLE_STATE_HPP
#define ALOHA_PUZZLE_STATE_HPP

#include "Grid.hpp"

class State {
public:
    State();
    ~State();



private:
    Grid *grid;
    int f;
    int g;
    int h;
};


#endif //ALOHA_PUZZLE_STATE_HPP
