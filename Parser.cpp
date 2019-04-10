//
// Created by aloha on 18.03.19.
//

#include "Parser.hpp"
#include "Heuristics.hpp"

Parser::Parser(char **av, std::string & flag) {
    cnt = 0;
    start = new Field();

    if (flag == "f") {
        isValidInputArgs(av[2]);
        heuristic = av[3];
        run();
    }
    if (flag == "g") {
        heuristic = av[3];
        isValidGrid(std::stoi(av[2]));
        genRandomField();
    }
}

Parser::~Parser() {
}

Field* Parser::getField() {
    return start;
}

void Parser::isValidTile(int value) {
    if (value < 0 || value > field_size - 1)
        throw Exceptions("Error: Value out of range");

    const auto it = std::find(values.begin(), values.end(), value);
    if (it != values.end()) {
        throw "Duplicate value.";
    }

    start->addTile(value, cnt);
    values.push_back(value);
    cnt++;
}

void Parser::isValidGrid(int rows) {
    if (rows < MIN_ROWS && rows > MAX_ROWS)
        throw Exceptions("Error: Invalid rows value");
    field_rows = rows;
    field_size = rows * rows;
    genSolvedField();
    start->init(field_size, rows, heuristic, target);
}

void Parser::run() {
    bool isSolved = false;
    std::regex regexVal(R"(\d+)");
    std::string line;

    while (getline(ifs, line)) {
        std::stringstream ss(line);
        std::string str;
        while (ss >> str)
            if (!field_rows && std::regex_match(str, regexVal)) {
                isValidGrid(std::stoi(str));
            } else if (str.find('#') != std::string::npos) {
                break;
            } else if (std::regex_match(str, regexVal)) {
                isValidTile(std::stoi(str));
            } else {
                throw "Invalid value: " + str;
            }
    }
    if (!field_rows) {
        throw "No size.";
    }
    if (values.size() != field_rows * field_rows) {
        throw "Grid size is wrong.";
    }
    isSolved = snailChecking();
    if (!isSolved)
        throw Exceptions("PUZZLE IS UNSOLVABLE");
}

void Parser::isValidInputArgs(char *filename) {
    ifs.open(filename);
    if (!ifs.is_open())
        throw "Can't open file.";
    ifs.fail();
    ifs.exceptions(std::ifstream::badbit);
}

int Parser::countInv(std::vector<int> &arr) {
    int inv_count = 0;
    for (int i = 0; i < arr.size() - 1; i++) {
        for (int j = i + 1; j < arr.size(); j++) {
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
    throw "No zero on map";
}

bool Parser::snailChecking() {
    int invCurr = countInv(values);
    int invFinal = countInv(target);

    if (field_size % 2 == 0) {
        invCurr += int(retGapPos(values) / field_rows);
        invFinal += int(retGapPos(target) / field_rows);
    }
    return invCurr % 2 == invFinal % 2;
}

void Parser::generate() {
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
}

void Parser::genRandomField() {
    bool isSolved = false;

    while (1) {
        values.clear();
        generate();
        isSolved = snailChecking();
        if (isSolved)
            break;
    }

    for (auto it : values) {
        start->addTile(it, cnt);
        cnt++;
    }
}

void Parser::genSolvedField() {
    int val = 1;
    int left = 0;
    int top = 0;
    int right = field_rows;
    int bottom = field_rows;
    int a[field_rows][field_rows];

    while (top < bottom && left < right) {
        for (int i = top; i < bottom; i++) {
            a[left][i] = val++;
            solvable_pos.push_back(left * field_rows + i);
        }
        left++;

        for (int i = left; i < right; i++) {
            a[i][bottom - 1] = val++;
            solvable_pos.push_back(i * field_rows + bottom - 1);
        }
        bottom--;

        if (left < right)
        {
            for (int i = bottom - 1; i >= top; --i) {
                a[right - 1][i] = val++;
                solvable_pos.push_back((right - 1) * field_rows + i);
            }
            right--;
        }

        if (top < bottom)
        {
            for (int i = right - 1; i >= left; --i) {
                a[i][top] = val++;
                solvable_pos.push_back(i * field_rows + top);
            }
            top++;
        }
    }

    for (int i = 0; i < field_rows; ++i) {
        for (int j = 0; j < field_rows; ++j) {
            if (a[i][j] == field_size)
                target.push_back(0);
            else
                target.push_back(a[i][j]);
        }
    }
}
