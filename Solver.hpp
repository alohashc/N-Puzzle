//
// Created by aloha on 22.03.19.
//

#ifndef ALOHA_PUZZLE_SOLVER_HPP
#define ALOHA_PUZZLE_SOLVER_HPP

#include "Field.hpp"

class Solver {
public:
    Solver(Field*);
    ~Solver();

    void init(Field*);

    void aStar();
    std::string genHash(Tile*);
    void exitAndOutput(State*);
    void getChildren(State*);
    void createChildState(State*, int, int);
    void swapTiles(Tile&, Tile&);
    bool isExists(std::map<std::string, int> &, State&);
    std::string print(Tile*);


private:
    Field *field;
    int totalOpenedSets = 0;
    int maxOpenedSets = 0;
    int moves = 0;
    std::string hash_end;
    std::list<std::string> output;
    std::map<std::string, int> open;     // <HASH, F>
    std::map<std::string, int> closed;   // <HASH, F>
    std::priority_queue<State, std::vector<State>, compareQueue> queue;

};


#endif //ALOHA_PUZZLE_SOLVER_HPP
