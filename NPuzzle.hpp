//
// Created by aloha on 19.03.19.
//

#ifndef ALOHA_PUZZLE_NPUZZLE_HPP
#define ALOHA_PUZZLE_NPUZZLE_HPP

#include <iostream>
#include <vector>
#include <utility>
#include "Exceptions.hpp"

#define MIN_ROWS 3
#define MAX_ROWS 5

struct  s_tile {
    int     value;
    std::pair<int, int> curr_pos;
    std::pair<int, int> end_pos;
};

struct s_state {
    int                     f;
    int                     g;
    int                     h;
    int                     gap_pos;
    std::string             hash;
    s_state *               parent;
    s_tile  *               tiles;
    std::vector<s_state>    children;
};

struct compareQueue {
    bool operator()(const s_state &first, const s_state &second) {
        return first.f > second.f;
    }
};
#endif //ALOHA_PUZZLE_NPUZZLE_HPP
