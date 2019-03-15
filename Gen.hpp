//
// Created by aloha on 15.03.19.
//

#ifndef ALOHA_PUZZLE_GENERATOR_HPP
#define ALOHA_PUZZLE_GENERATOR_HPP


#include <vector>
#include <random>
#include <unordered_set>
#include <iostream>

class Gen {
public:
    Gen();
    ~Gen();

    void Init();


private:
    std::vector<int> grid;

};


#endif //ALOHA_PUZZLE_GENERATOR_HPP
