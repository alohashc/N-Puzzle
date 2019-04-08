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
        this->start->init(this->field_size, this->field_rows, this->heuristic, this->target);
        this->genRandomField(std::stoi(av[2]));
    }
}

Parser::~Parser() {

}

void Parser::print_grid(std::vector<int> &arr) {
    for (int it : arr)
        std::cout << it << std::endl;
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
    this->values.push_back(value);
    this->cnt++;
}

void Parser::isValidGrid(int rows) {
    if (rows < MIN_ROWS && rows > MAX_ROWS)
        throw Exceptions("Error: Invalid rows value");
    this->field_rows = rows;
    this->field_size = rows * rows;
    this->genSolvedField();
//    this->start->init(this->field_size, rows, this->heuristic, this->target);
}

void Parser::run() {
    bool isSolved = false;
    std::regex values("\\d+");
    std::regex comments("\\#[\\s*a-zA-Z]+[a-zA-Z]$");
    std::string line;

    while (getline(this->ifs, line)) {
        std::sregex_iterator begin(line.begin(), line.end(), values);
        std::sregex_iterator end;

        for (; begin != end; ++begin) {
            if (!this->field_rows) {
                this->isValidGrid(std::stoi((*begin).str()));
                this->start->init(this->field_size, this->field_rows, this->heuristic, this->target);
                if (line.size() > 1)
                    throw Exceptions("Error: Invalid input field size");
                continue;
            }
            this->isValidTile(std::stoi((*begin).str()));
        }
    }
    isSolved = this->snailChecking();
    if (!isSolved)
        throw Exceptions("ERROR: NOT SOLVED");
//    this->start->print_tiles();
}

void Parser::isValidInputArgs(char *filename) {
    this->ifs.open(filename);
    this->ifs.fail();
    this->ifs.exceptions(std::ifstream::badbit);
}

int Parser::gapFromBottom() {
    int cnt_row = 0;
    // start from bottom-right corner of matrix
    for (int i = this->field_size; i >= 0; i--) {
        if (i % this->field_rows == 0)
            cnt_row++;
        if (this->values[i - 1] == 0)
            return cnt_row;
    }
}

int Parser::countInv(std::vector<int> &arr) {
    int inv_count = 0;
    for (int i = 0; i < arr.size() - 1; i++)
    {
        for (int j = i + 1; j < arr.size(); j++)
        {
            // count pairs(i, j) such that i appears
            // before j, but i > j.
            if (arr[j] && arr[i] && arr[i] > arr[j])
                inv_count++;
        }
    }
    return inv_count;
}

int Parser::retGapPos(std::vector<int> & arr) {
    for (int i = 0; i < arr.size(); ++i)
        if (arr[i] == 0)
            return i;
}

bool Parser::snailChecking() {
    int invCurr = this->countInv(this->values);
    int invFinal = this->countInv(this->target);

    if (this->field_size % 2 == 0) {
        invCurr += int(this->retGapPos(this->values) / this->field_rows);
        invFinal += int(this->retGapPos(this->target) / this->field_rows);
    }
    return invCurr % 2 == invFinal % 2;
}

bool Parser::checkSolving() {
    int inv = this->countInv(this->values);
    int gap_row = this->gapFromBottom();

    if (this->field_rows % 2 != 0)
        return !(inv % 2);
    else{
        if (gap_row % 2)
            return !(inv % 2);
        else
            return inv % 2;
    }
}

void Parser::Generate() {
    std::vector<int> possibleValues;
    for (int i = 0; i < field_size; ++i) {
        possibleValues.push_back(i);
    }

    int number = 0;
    int index = 0;
    srand((int)time(0));
    std::vector<int> tmp(field_size);
    for (auto &it : tmp) {
        index = rand() % possibleValues.size();
        number = possibleValues[index];
        it = number;
        const auto delIt = std::find(possibleValues.begin(), possibleValues.end(), number);
        possibleValues.erase(delIt);
    }
    values = tmp;
    print_grid(values);
}

void Parser::genRandomField(int rows) {
    bool isSolved = false;
    if (rows < MIN_ROWS && rows > MAX_ROWS)
        throw Exceptions("Error: Invalid rows value");
    this->start->init(rows * rows, rows, this->heuristic, this->target);

    int i = 0;
    while (1) {
        std::cout << "Generate iter: " << i << std::endl;
        ++i;
        values.clear();
        Generate();
        isSolved = this->snailChecking();
        std::cout << "WTF: " << isSolved << std::endl;
        if (isSolved)
            break;
    }

    for (auto it : this->values) {
        this->start->addTile(it, this->cnt);
        this->cnt++;
    }
    if (!isSolved)
        throw Exceptions("ERROR: NOT SOLVED");
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
