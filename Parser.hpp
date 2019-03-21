//
// Created by aloha on 18.03.19.
//

#ifndef ALOHA_PUZZLE_PARSER_HPP
#define ALOHA_PUZZLE_PARSER_HPP

#include "Field.hpp"
#include <iostream>
#include <fstream>
#include <regex>

class Parser {
public:
    Parser();
    ~Parser();

    void run(char **);

private:
    Field   *start;
    int    field_size;
    int    field_rows;
};


#endif //ALOHA_PUZZLE_PARSER_HPP
