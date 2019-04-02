//
// Created by aloha on 22.03.19.
//

#include "Solver.hpp"

Solver::Solver(Field *start) {
    this->init(start);
//    this->aStar();
}

Solver::~Solver() {

}

std::string& Solver::genHash(s_tile *tiles) {
    std::string hash;

    for (int i = 0; i < this->field->getSize(); ++i) {
        hash += std::to_string(tiles[i].value) + ',';
    }

    return hash;
}

void Solver::init(Field *start) {
    this->field = start;
}