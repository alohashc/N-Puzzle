#include "Gen.hpp"
#include "Parser.hpp"
#include "Solver.hpp"

void inputArgs(int ac) {
    if (ac != 3) {
        std::cerr << "Usage: ./npuzzle <file> <heuristic>" << std::endl;
        std::cerr << "Available heuristics: " << std::endl;
        exit(1);
    }
}

int main(int ac, char**av) {
    inputArgs(ac);
    try {
        Parser parser(av);
//        Solver solver();
    }
    catch (Exceptions &e) {
        e.what();
    }
    return 0;
}