//
// Created by aloha on 18.03.19.
//

#ifndef ALOHA_PUZZLE_GRID_HPP
#define ALOHA_PUZZLE_GRID_HPP


struct s_pos{
    int x;
    int y;
};

class Grid {
public:
    Grid();
    ~Grid();

private:
    s_pos pos;
    s_pos target;
};


#endif //ALOHA_PUZZLE_GRID_HPP
