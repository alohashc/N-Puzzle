//
// Created by aloha on 18.03.19.
//

#ifndef ALOHA_PUZZLE_PARSER_HPP
#define ALOHA_PUZZLE_PARSER_HPP

#include "Field.hpp"

class Parser {
public:
    Parser(char **, std::string&);
    ~Parser();

    void run();

    void isValidInputArgs(char *);
    void isValidGrid(int);
    void isValidTile(int);
    void genSolvedField();
    void genRandomField();
    void generate();

    int countInv(std::vector<int> &);
    int retGapPos(std::vector<int> &);
    bool snailChecking();

    Field* getField();

private:
    Field   *start;
    int field_size = 0;
    int field_rows = 0;
    int cnt;
    std::vector<int> solvable_pos;
    std::vector<int> target;
    std::vector<int> values;
    std::string heuristic;
    std::ifstream ifs;

};


#endif //ALOHA_PUZZLE_PARSER_HPP
