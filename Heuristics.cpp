//
// Created by aloha on 22.03.19.
//

#include "Heuristics.hpp"

Heuristics::Heuristics() {
    this->size = 0;
    this->tile = nullptr;
    this->name = "";
    this->heuristics.emplace("m", &Heuristics::manhattan);
}


Heuristics::~Heuristics() {

}

Heuristics& Heuristics::operator=(const Heuristics &src) {
    this->name = src.name;
    this->tile = src.tile;
    this->size = src.size;
    this->heuristics = src.heuristics;
}

int Heuristics::getH(s_tile *tiles) {
    this->tile = tiles;
    int (Heuristics::*f)();
    f = this->heuristics.at(this->name);

    return (this->*f)();
}

void Heuristics::init(std::string & name, int size) {
    if (!this->heuristics[name])
        throw Exceptions("Error: Invalid heuristic");
    this->name = name;
    this->size = size;
}

int Heuristics::manhattan() {
    int     res_h = 0;

    for (int i = 0; i < this->size; ++i)
        res_h += std::abs(this->tile[i].curr_pos.first - this->tile[i].end_pos.first) +
                std::abs(this->tile[i].curr_pos.second - this->tile[i].end_pos.second);
    return (res_h);
}