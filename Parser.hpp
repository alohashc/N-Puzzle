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
    Parser(char **);
    ~Parser();

    void run();
    void isValidInputArgs(char **);

private:
    Field   *start;
    int    field_size;
    int    field_rows;
    std::ifstream ifs;
};


#endif //ALOHA_PUZZLE_PARSER_HPP
