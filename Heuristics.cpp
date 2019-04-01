//
// Created by aloha on 22.03.19.
//

#include "Heuristics.hpp"

Heuristics::Heuristics() {
    this->heuristics.emplace("m", &Heuristics::manhattan);
}

Heuristics::~Heuristics() {

}

void Heuristics::init(std::string & name, s_tile *tiles, int size) {
    if (!this->heuristics[name])
        throw Exceptions("Error: Invalid heuristic");
    this->name = name;
    this->tile = tiles;
    this->size = size;
}

int Heuristics::manhattan() {
    int     res_h = 0;

    for (int i = 0; i < this->size; ++i)
        res_h += std::abs(this->tile[i].curr_pos.first - this->tile[i].end_pos.first) +
                std::abs(this->tile[i].curr_pos.second - this->tile[i].end_pos.second);
    return (res_h);
}