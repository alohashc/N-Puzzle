//
// Created by aloha on 21.03.19.
//

#ifndef ALOHA_PUZZLE_FIELD_HPP
#define ALOHA_PUZZLE_FIELD_HPP

#include "NPuzzle.hpp"
#include "Heuristics.hpp"
#include <set>

class Field {
public:

    Field();
    ~Field();

    void    init(int, int, std::string&);
    void    addTile(int, int);

    Field &operator=(const Field &);


    int findFinalPos(int);
    void genSolvedGrid();
    s_tile * getTiles() const;
    int &getSize();
    int getHeuristic(s_tile*);
    void print_tiles();
    void print_target();

private:
    int     field_size;
    int     field_rows;
    std::vector<int>  target;
    Heuristics heuristics;
    int     gap;
    s_tile* tiles;
};


#endif //ALOHA_PUZZLE_FIELD_HPP
