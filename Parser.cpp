//
// Created by aloha on 18.03.19.
//

#include "Parser.hpp"
#include "Heuristics.hpp"

Parser::Parser(char **av) {
    this->cnt = 0;
    this->start = new Field();
    this->isValidInputArgs(av[1]);
    this->run();

}

Parser::~Parser() {

}

void Parser::print_grid() {
    for (int setOfValue : this->setOfValues)
        std::cerr << setOfValue << std::endl;
    std::cout << "---------------" << std::endl;
}

void Parser::setStartField() {
//    this->start->init();
}

void Parser::isValidTile(int value) {
    if (value < 0 || value > this->field_size - 1)
        throw Exceptions("Error: Value out of range");

    auto len = this->setOfValues.size();
    this->setOfValues.insert(value);
    if (this->setOfValues.size() == len)
        throw Exceptions("Error: Duplicate value");
    this->start->addTile(value, this->cnt);
    this->cnt++;
}

void Parser::isValidGrid(int rows) {
    if (rows < MIN_ROWS && rows > MAX_ROWS)
        throw Exceptions("Error: Invalid rows value");
    this->field_rows = rows;
    this->field_size = rows * rows;
    this->start->init(this->field_size, rows);
}

void Parser::run() {
//    std::regex comments(R"(^#[a-zA-Z\s\d]+|^\s+#[a-zA-Z\s\d]+|^[\d\s]+#[a-zA-Z\s\d]+)");
    std::regex values("\\d+");
    std::string line;

    while (getline(this->ifs, line)) {
        std::sregex_iterator begin(line.begin(), line.end(), values);
        std::sregex_iterator end;

        for (; begin != end; ++begin) {
            if (!this->field_rows) {
                this->isValidGrid(std::stoi((*begin).str()));
                continue;
            }
            this->isValidTile(std::stoi((*begin).str()));
        }
    }
    this->start->print_tiles();
}

void Parser::isValidInputArgs(char *filename) {
    this->ifs.open(filename);
    this->ifs.fail();
    this->ifs.exceptions(std::ifstream::badbit);
}
