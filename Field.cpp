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
    if (this == &src)
        return *this;
    field_rows = src.field_rows;
    field_size = src.field_size;
    gap = src.gap;
    tiles = src.getTiles();
    heuristics = src.heuristics;
    target = src.target;

    return *this;
}

Tile* Field::getTiles() const{
    return tiles;
}

int& Field::getSize() {
    return field_size;
}

int& Field::getRows() {
    return field_rows;
}

int& Field::getGapPos() {
    return gap;
}

int Field::getHeuristic(Tile *tiles) {
    return heuristics.getH(tiles);
}

std::string Field::genHashEnd() {
    std::string hash;

    for (auto it : target)
       hash += std::to_string(it) + ',';
    return hash;
}

int Field::findFinalPos(int value) {
    const auto it = std::find(target.begin(), target.end(), value);
    if (it == target.end())
        throw "Couldn't find element in target.";

    return it - target.begin();
}

void Field::addTile(int value, int pos) {
    int solved_pos = findFinalPos(value);

    tiles[pos].value = value;
    tiles[pos].curr_pos.first = pos % field_rows;
    tiles[pos].curr_pos.second = pos / field_rows;
    tiles[pos].end_pos.first = solved_pos % field_rows;
    tiles[pos].end_pos.second = solved_pos / field_rows;

    if (!value)
        gap = pos;
}

void Field::init(int size, int rows, std::string & heuristic, std::vector<int> & target) {
    field_size = size;
    field_rows = rows;
    this->target = target;
    tiles = new Tile[field_size];
    heuristics.init(heuristic, size);
}