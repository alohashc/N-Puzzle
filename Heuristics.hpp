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
    int getH(s_tile*);
    void init(std::string&, int);

private:
    int     manhattan();
    int     misplacedTile();

    std::string name;
    s_tile *tile;
    int     size;
    std::map<std::string, int (Heuristics::*)()> heuristics;
};


#endif //ALOHA_PUZZLE_HEURISTICS_HPP
