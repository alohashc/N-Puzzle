//
// Created by aloha on 22.03.19.
//

#include "Heuristics.hpp"

Heuristics::Heuristics() {
    this->size = 0;
    this->tile = nullptr;
    this->name = "";
    this->heuristics.emplace("m", &Heuristics::manhattan);
    this->heuristics.emplace("mt", &Heuristics::misplacedTile);
    this->heuristics.emplace("eu", &Heuristics::euclidean);
    this->heuristics.emplace("lc", &Heuristics::LinearConflict);
    this->heuristics.emplace("ct", &Heuristics::cornerTiles);
}


Heuristics::~Heuristics() {

}

Heuristics& Heuristics::operator=(const Heuristics &src) {
    this->name = src.name;
    this->tile = src.tile;
    this->size = src.size;
    this->rows = sqrt(this->size);
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

int Heuristics::misplacedTile() {
    int cnt = 0;

    for (int i = 0; i < this->size; ++i){

        if (this->tile[i].curr_pos.first != this->tile[i].end_pos.first ||
                this->tile[i].curr_pos.second != this->tile[i].end_pos.second)
            cnt++;
    }
    return cnt;
}

int Heuristics::euclidean() {
    int res_h = 0;

    for (int i = 0; i < this->size; ++i){
        res_h += sqrt(pow((this->tile[i].curr_pos.first - this->tile[i].end_pos.first), 2) +
                             pow((this->tile[i].curr_pos.second != this->tile[i].end_pos.second), 2));
    }
    return res_h;
}

int			Heuristics::LinearConflict()
{
    int conflicts = 0;

    for (int i = 0; i < size; ++i)
    {
        for (int j = tile[i].curr_pos.second * rows; j < (tile[i].curr_pos.second + 1) * rows; ++j) // check just the same row
        {
            if (tile[i].value != tile[j].value			// jump itself
                && tile[i].curr_pos.second == tile[i].end_pos.second 		// i is in its goal row
                && tile[j].curr_pos.second == tile[j].end_pos.second 		// j is in its goal row
                && tile[i].curr_pos.first > tile[j].curr_pos.first			// i is to the right of j
                && tile[i].end_pos.first <= tile[j].end_pos.first)	// i goal is to the left of j position (or in j position)
            {
                ++conflicts;
            }
        }
        for (int j = tile[i].curr_pos.first * rows; j < (tile[i].curr_pos.first + 1) * rows; j += rows) // check just the same col
        {
            if (tile[i].value != tile[j].value			// jump itself
                && tile[i].curr_pos.first == tile[i].end_pos.first 		// i is in its goal col
                && tile[j].curr_pos.first == tile[j].end_pos.first 		// j is in its goal col
                && tile[i].curr_pos.second > tile[j].curr_pos.second			// i is under j
                && tile[i].end_pos.second <= tile[j].end_pos.second)	// i goal is over j position (or in j position)
            {
                ++conflicts;
            }
        }
    }
    return Heuristics::manhattan() + 2 * conflicts;
}

int Heuristics::cornerTiles() {
    int conflicts = 0;

    if (tile[0].value != 1) {
        if (tile[1].value == 2 || tile[rows].value == rows + 1)
            conflicts += 1;
    }
    if (tile[rows - 1].value != rows) {
        if (tile[rows - 2].value == rows - 1 || tile[rows * 2 - 1].value == rows + 1)
            conflicts += 1;
    }
    if (tile[size - rows].value != rows * 3 - 2) {
        if (tile[size - rows].value == rows * 3 - 1 || tile[size - rows + 1].value == rows * 3 - 3)
            conflicts += 1;
    }
    if (tile[size - 1].value != rows * 2 - 1) {
        if (tile[size - 2].value == rows * 2 || tile[size - rows - 1].value == rows * 2 - 2)
            conflicts += 1;
    }
    return Heuristics::manhattan() + 2 * conflicts;

}