//
// Created by aloha on 18.03.19.
//

#ifndef ALOHA_PUZZLE_PARSER_HPP
#define ALOHA_PUZZLE_PARSER_HPP

#include "State.hpp"
#include <iostream>
#include <fstream>
#include <regex>

class Parser {
public:
    Parser();
    ~Parser();

    void run(std::string &);
    void set_state(std::vector<std::string> &);

private:
    State start;
    int     grid_size;
};


#endif //ALOHA_PUZZLE_PARSER_HPP
