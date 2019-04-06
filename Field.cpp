//
// Created by aloha on 21.03.19.
//

#include "Field.hpp"

Field::Field() {
    this->field_size = 0;
    this->field_rows = 0;
    this->gap = 0;
    this->tiles = nullptr;
}


Field::~Field() {

}

Field& Field::operator=(const Field &src) {
    this->field_rows = src.field_rows;
    this->field_size = src.field_size;
    this->gap = src.gap;
    this->tiles = src.getTiles();
    this->heuristics = src.heuristics;
    this->target = src.target;
}

void Field::print_tiles() {
    for (int i = 0; i < this->field_size; ++i) {
        std::cerr << this->tiles[i].value << std::endl;
        std::cerr << this->tiles[i].curr_pos.first << " " << this->tiles[i].curr_pos.second << std::endl;
    }
}

s_tile* Field::getTiles() const{
    return this->tiles;
}

int& Field::getSize() {
    return this->field_size;
}

int& Field::getRows() {
    return this->field_rows;
}

int& Field::getGapPos() {
    return this->gap;
}

int Field::getHeuristic(s_tile *tiles) {
    return this->heuristics.getH(tiles);
}

std::string Field::genHashEnd() {
    std::string hash;

    for (auto it : this->target)
       hash += std::to_string(it) + ',';
    return hash;
}

int Field::findFinalPos(int value) {
    for (int i = 0; i < this->target.size(); ++i) {
        if (this->target[i] == value)
            return i;
    }
}

void Field::addTile(int value, int pos) {
    int solved_pos = findFinalPos(value);

    this->tiles[pos].value = value;
    this->tiles[pos].curr_pos.first = pos % this->field_rows;
    this->tiles[pos].curr_pos.second = pos / this->field_rows;
    this->tiles[pos].end_pos.first = solved_pos % this->field_rows;
    this->tiles[pos].end_pos.second = solved_pos / this->field_rows;

    if (value == 0)
        this->gap = pos;
}

void Field::print_target() {
    for (auto it: this->target)
        std::cerr << it << std::endl;
}

void Field::init(int size, int rows, std::string & heuristic, std::vector<int> & target) {
    this->field_size = size;
    this->field_rows = rows;
    this->target = target;
    this->tiles = new s_tile[this->field_size];
    this->heuristics.init(heuristic, size);
}