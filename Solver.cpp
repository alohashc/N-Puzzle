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

//void Solver::aStar() {
//    s_state curr;
//
//    this->open.emplace("", curr);
//}

std::string Solver::genHash(s_tile *tiles) {
    std::string hash_str;

    for (int i = 0; i < this->field->getSize(); ++i) {
        hash_str += std::to_string(tiles[i].value) + ',';
    }

    return hash_str;
}

void Solver::init(Field *field) {
    s_state start;

    this->field = field;
    start.tiles = field->getTiles();
    start.hash = this->genHash(start.tiles);
    start.g = 0;
    start.h = field->getHeuristic(start.tiles);
    start.f = start.g + start.h;
}