//
// Created by aloha on 18.03.19.
//

#ifndef ALOHA_PUZZLE_PARSER_HPP
#define ALOHA_PUZZLE_PARSER_HPP

#include "Field.hpp"
#include <iostream>
#include <fstream>
#include <regex>
#include <random>
#include <unordered_set>
#include <cstdlib>
#include <ctime>

class Parser {
public:
    Parser(char **, std::string&);
    ~Parser();

    void run();
    void isValidInputArgs(char *);
    void isValidGrid(int);
    void isValidTile(int);
    Field* getField();
    void genSolvedField();
    void genRandomField(int);
    bool checkSolving();
    bool snailChecking();
    int countInv(std::vector<int> &);
    int gapFromBottom();
    int retGapPos(std::vector<int> &);
    void Generate();
    void print_grid(std::vector<int>&);

private:
    Field   *start;
    int    field_size;
    std::vector<int> solvable_pos;
    std::vector<int> target;
    std::vector<int> values;
    int    field_rows;
    std::unordered_set<int> setOfValues;
    std::ifstream ifs;
    std::string   heuristic;
    int     cnt;
};


#endif //ALOHA_PUZZLE_PARSER_HPP
