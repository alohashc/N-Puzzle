//
// Created by aloha on 21.03.19.
//

#ifndef ALOHA_PUZZLE_FIELD_HPP
#define ALOHA_PUZZLE_FIELD_HPP

#include "NPuzzle.hpp"
#include "Heuristics.hpp"

class Field {
public:

    Field();
    ~Field();

    void    init(int, int, std::string&, std::vector<int> &);
    void    addTile(int, int);

    Field &operator=(const Field &);

    int findFinalPos(int);
    std::string genHashEnd();

    Tile * getTiles() const;
    int &getSize();
    int &getRows();
    int &getGapPos();
    int getHeuristic(Tile*);

private:
    std::vector<int>  target;
    Heuristics heuristics;
    Tile* tiles;
    int field_size;
    int field_rows;
    int gap;
};


#endif //ALOHA_PUZZLE_FIELD_HPP
