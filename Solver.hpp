//
// Created by aloha on 22.03.19.
//

#ifndef ALOHA_PUZZLE_SOLVER_HPP
#define ALOHA_PUZZLE_SOLVER_HPP

#include "Field.hpp"
#include <queue>
#include <algorithm>
#include <sstream>
#include <list>

class Solver {
public:
    Solver(Field*);
    ~Solver();

    void init(Field*);

    void aStar();
    std::string genHash(s_tile*);
    void exitAndOutput(s_state*);
    void getChildren(s_state*);
    void createChildState(s_state*, int, int);
    void swapTiles(s_tile&, s_tile&);
    bool isExists(std::map<std::string, int> &, s_state&);
    std::string print(s_tile*);
    void printT(s_state*);
    bool isErased(std::string hash);


private:
    std::list<std::string>		_output;
    std::set<std::string>		_erased;
    Field *field;
    std::string                 hash_end;
    std::map<std::string, int> open;     // <HASH, F>
    std::map<std::string, int> closed;   // <HASH, F>
    std::priority_queue<s_state, std::vector<s_state>, s_cmp>	queue;
};


#endif //ALOHA_PUZZLE_SOLVER_HPP
