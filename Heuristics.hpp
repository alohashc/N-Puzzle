//
// Created by aloha on 22.03.19.
//

#ifndef ALOHA_PUZZLE_HEURISTICS_HPP
#define ALOHA_PUZZLE_HEURISTICS_HPP

#include "NPuzzle.hpp"
#include <map>

typedef int (*f)(s_tile*, int);

class Heuristics {
public:
    Heuristics();
    ~Heuristics();

    static void init();
    static void setH(std::string &h);

private:
    int     manhattan(s_tile *tile, int size);
};


#endif //ALOHA_PUZZLE_HEURISTICS_HPP
