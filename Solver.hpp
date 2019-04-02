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
    std::string & genHash(s_tile*);

private:
    Field *field;
    std::map<std::string, int> open;
    std::map<std::string, int> closed;
};


#endif //ALOHA_PUZZLE_SOLVER_HPP
