//
// Created by aloha on 22.03.19.
//

#ifndef ALOHA_PUZZLE_SOLVER_HPP
#define ALOHA_PUZZLE_SOLVER_HPP

#include "Field.hpp"
#include <queue>

class Solver {
public:
    Solver(Field*);
    ~Solver();

    void init(Field*);

    void aStar();
    std::string genHash(s_tile*);

private:
    Field *field;
    std::map<std::string, int> open;     // <HASH, F>
    std::map<std::string, int> closed;   // <HASH, F>
    std::priority_queue<s_state, std::vector<s_state>, s_cmp>	queue;
};


#endif //ALOHA_PUZZLE_SOLVER_HPP
