//
// Created by aloha on 18.03.19.
//

#ifndef ALOHA_PUZZLE_PARSER_HPP
#define ALOHA_PUZZLE_PARSER_HPP

#include "Field.hpp"
#include <iostream>
#include <fstream>
#include <regex>
#include <set>

class Parser {
public:
    Parser(char **);
    ~Parser();

    void run();
    void isValidInputArgs(char *);
    void isValidGrid(int);
    void isValidTile(int);

private:
    Field   *start;
    int    field_size;
    int    field_rows;
    std::set<int> setOfValues;
    std::ifstream ifs;
};


#endif //ALOHA_PUZZLE_PARSER_HPP
