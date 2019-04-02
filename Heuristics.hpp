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

    Heuristics &operator=(const Heuristics &rhs);
    void init(std::string&, s_tile *, int);

private:
    int     manhattan();
    std::string name;
    s_tile *tile;
    int     size;
    std::map<std::string, int (Heuristics::*)()> heuristics;
};


#endif //ALOHA_PUZZLE_HEURISTICS_HPP
