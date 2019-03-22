//
// Created by aloha on 22.03.19.
//

#include "Heuristics.hpp"

Heuristics::Heuristics() {
}

Heuristics::~Heuristics() {

}

void Heuristics::init() {
}

void Heuristics::setH(std::string &h) {
}

int Heuristics::manhattan(s_tile *tile, int size) {
    int     res_h = 0;

    for (int i = 0; i < size; ++i)
        res_h += std::abs(tile[i].curr_pos.x - tile[i].end_pos.x) +
                std::abs(tile[i].curr_pos.y - tile[i].end_pos.y);
    return (res_h);
}