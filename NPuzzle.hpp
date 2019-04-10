//
// Created by aloha on 19.03.19.
//

#ifndef ALOHA_PUZZLE_NPUZZLE_HPP
#define ALOHA_PUZZLE_NPUZZLE_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <regex>
#include <random>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <queue>
#include <algorithm>
#include <list>
#include "Exceptions.hpp"

#define MIN_ROWS 3
#define MAX_ROWS 5

struct  Tile {
    int value;
    std::pair<int, int> curr_pos;
    std::pair<int, int> end_pos;
};

struct State {
    State *parent;
    Tile  *tiles;
    int f;
    int g;
    int h;
    int gap_pos;
    std::string hash;
    std::vector<State> children;
};

struct compareQueue {
    bool operator()(const State &first, const State &second) {
        return first.f > second.f;
    }
};
#endif //ALOHA_PUZZLE_NPUZZLE_HPP
