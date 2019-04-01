//
// Created by aloha on 21.03.19.
//

#include "Field.hpp"

Field::Field() {

}

Field::~Field() {

}

void Field::print_tiles() {
    for (int i = 0; i < this->field_size; ++i) {
        std::cerr << this->tiles[i].value << std::endl;
        std::cerr << this->tiles[i].curr_pos.first << " " << this->tiles[i].curr_pos.second << std::endl;
    }
}

void Field::genSolvedGrid() {
    int val = 1;
    int left = 0;
    int top = 0;
    int right = this->field_rows;
    int bottom = this->field_rows;
    int a[this->field_rows][this->field_rows];

    while (top < bottom && left < right) {
        if (val == this->field_size)
            val = 0;
        for (int i = top; i < bottom; i++)
            a[left][i] = val++;
        left++;

        for (int i = left; i < right; i++)
            a[i][bottom - 1] = val++;
        bottom--;

        if (left < right)
        {
            for (int i = bottom - 1; i >= top; --i)
                a[right - 1][i] = val++;
            right--;
        }

        if (top < bottom)
        {
            for (int i = right - 1; i >= left; --i)
                a[i][top] = val++;
            top++;
        }
    }

    for (int i = 0; i < this->field_rows; ++i) {
        for (int j = 0; j < this->field_rows; ++j) {
            this->target.push_back(a[i][j]);
        }
    }
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
    std::cout << this->tiles[pos].end_pos.first << this->tiles[pos].end_pos.second << std::endl;
    if (value == 0)
        this->gap = pos;
}

void Field::print_target() {
    for (auto it: this->target)
        std::cerr << it << std::endl;
}

void Field::init(int size, int rows, std::string & heuristic) {
    this->field_size = size;
    this->field_rows = rows;
    this->tiles = new s_tile[this->field_size];
    this->genSolvedGrid();
    this->heuristics.init(heuristic, this->tiles, size);
}