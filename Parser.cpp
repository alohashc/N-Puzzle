//
// Created by aloha on 18.03.19.
//

#include "Parser.hpp"
#include "Heuristics.hpp"

Parser::Parser(char **av, std::string & flag) {
    this->cnt = 0;
    this->start = new Field();

    if (flag == "f") {
        this->isValidInputArgs(av[2]);
        this->heuristic = av[3];
        this->run();
    }
    if (flag == "g") {
        this->heuristic = av[3];
        isValidGrid(std::stoi(av[2]));
        this->genSolvedField();
        this->genRandomField(std::stoi(av[2]));
//        this->start->init(this->field_size, rows, this->heuristic, this->target);
//        this->heuristic = av[3];
//        isValidGrid(std::stoi(av[2]));
    }
}

Parser::~Parser() {

}

void Parser::print_grid() {
    for (int setOfValue : this->setOfValues)
        std::cerr << setOfValue << std::endl;
    std::cout << "---------------" << std::endl;
}

Field* Parser::getField() {
    return this->start;
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
    this->genSolvedField();
    this->start->init(this->field_size, rows, this->heuristic, this->target);
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
//    this->start->print_tiles();
}

void Parser::isValidInputArgs(char *filename) {
    this->ifs.open(filename);
    this->ifs.fail();
    this->ifs.exceptions(std::ifstream::badbit);
}

void Parser::genRandomField(int rows) {
    if (rows < MIN_ROWS && rows > MAX_ROWS)
        throw Exceptions("Error: Invalid rows value");
    this->start->init(rows * rows, rows, this->heuristic, this->target);
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, rows * rows - 1);

    while (this->setOfValues.size() < rows * rows){
        int res = distribution(generator);
        this->setOfValues.insert(res);
    }
    for (auto it : this->setOfValues) {
        this->start->addTile(it, this->cnt);
        this->cnt++;
    }
}

void Parser::genSolvedField() {
    int val = 1;
    int left = 0;
    int top = 0;
    int right = this->field_rows;
    int bottom = this->field_rows;
    int a[this->field_rows][this->field_rows];

    while (top < bottom && left < right) {
        for (int i = top; i < bottom; i++) {
            a[left][i] = val++;
            this->solvable_pos.push_back(left * this->field_rows + i);
        }
        left++;

        for (int i = left; i < right; i++) {
            a[i][bottom - 1] = val++;
            this->solvable_pos.push_back(i * this->field_rows + bottom - 1);
        }
        bottom--;

        if (left < right)
        {
            for (int i = bottom - 1; i >= top; --i) {
                a[right - 1][i] = val++;
                this->solvable_pos.push_back((right - 1) * this->field_rows + i);
            }
            right--;
        }

        if (top < bottom)
        {
            for (int i = right - 1; i >= left; --i) {
                a[i][top] = val++;
                this->solvable_pos.push_back(i * this->field_rows + top);
            }
            top++;
        }
    }

    for (int i = 0; i < this->field_rows; ++i) {
        for (int j = 0; j < this->field_rows; ++j) {
            if (a[i][j] == this->field_size)
                this->target.push_back(0);
            else
                this->target.push_back(a[i][j]);
        }
    }
}
