//
// Created by aloha on 15.03.19.
//

#include "Gen.hpp"

Gen::Gen() {

}

Gen::~Gen() {

}

void Gen::Init() {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 8);

    std::unordered_set<int> s;

    while (s.size() <= 8){
        int res = distribution(generator);
        s.insert(res);
    }

    for (auto it = s.begin(); it != s.end(); it++)
        std::cout << *it << std::endl;
}