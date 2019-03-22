//
// Created by aloha on 18.03.19.
//

#include "Parser.hpp"
#include "Heuristics.hpp"

Parser::Parser(char **av) {
    this->isValidInputArgs(av);
    this->run();

}

Parser::~Parser() {

}


void Parser::run() {
    std::regex comments(R"(^#[a-zA-Z\s\d]+|^\s+#[a-zA-Z\s\d]+|^[\d\s]+#[a-zA-Z\s\d]+)");
    std::regex values("\\d+");
    std::string line;

    while (getline(this->ifs, line)) {
        auto begin = std::regex_iterator<std::string::iterator>(line.begin(), line.end(), values);
        auto end = std::regex_iterator<std::string::iterator>();

        for (std::regex_iterator<std::string::iterator> it = begin; it != end; ++it) {

        }
    }
}

void Parser::isValidInputArgs(char **av) {
    this->ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    this->ifs.open(av[1]);
    this->ifs.exceptions(std::ifstream::badbit);
}

//// TODO: CHECK IF PASS DIRECTORY INSTEAD FILE
//void Parser::run(std::string &filename) {
//    std::regex comments(R"(^#[a-zA-Z\s\d]+|^\s+#[a-zA-Z\s\d]+|^[\d\s]+#[a-zA-Z\s\d]+)");
//    std::regex size(R"(^\d)");
//    std::regex values(R"(^\d+\s+\d+\s+\d+\s+\d+\s+)");
//    std::ifstream ifs;
//    std::string line;
//    bool is_com;
//    bool is_size;
//    bool is_values;
//    int count_val_lines = 0;
//    std::vector<std::string> v;
//
//    ifs.open(filename);
//
//    if (!ifs.is_open()) {
//        std::cout << "Error opening file" << std::endl;
//        exit(0);
//    }
//
//    while (getline(ifs, line)) {
//        is_com = std::regex_match(line, comments);
//        is_size = std::regex_match(line, size);
//        std::cout << is_size << std::endl;
//        is_values = std::regex_match(line, values);
//        if (!is_com && !is_size && !is_values) {
//            std::cout << "Error: invalid input file" << std::endl;
//            exit(0);
//        }
//        if (is_size) {
//            this->field_size = std::stoi(line);
//            std::cout << this->field_size << std::endl;
//            count_val_lines++;
//        }
//        if (is_values) {
//            count_val_lines++;
//            v.push_back(line);
//        }
//    }
//    if (count_val_lines != this->field_size + 1) {
//        std::cout << "Error: invalid values" << std::endl;
//        exit(0);
//    }
//}
