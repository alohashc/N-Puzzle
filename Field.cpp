//
// Created by aloha on 21.03.19.
//

#include "Field.hpp"

Field::Field() {

}

Field::~Field() {

}

void Field::print_tiles() {
    for (int i = 0; i < this->filed_size; ++i) {
        std::cerr << this->tiles[i].value << std::endl;
        std::cerr << this->tiles[i].curr_pos.x << " " << this->tiles[i].curr_pos.y << std::endl;
    }
}

void Field::addTile(int value, int pos) {
    this->tiles[pos].value = value;
    this->tiles[pos].curr_pos.x = pos % this->field_rows;
    this->tiles[pos].curr_pos.y = pos / this->field_rows;
    if (value == 0)
        this->gap = pos;
}

void Field::init(int size, int rows) {
    this->filed_size = size;
    this->field_rows = rows;
    this->tiles = new s_tile[this->filed_size];
}