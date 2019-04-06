#include "Gen.hpp"
#include "Parser.hpp"
#include "Solver.hpp"

void usage() {
    std::cerr << "Usage: ./npuzzle <flag: 'f'=file or 'g'=generate>" << std::endl;
    std::cerr << "       ./npuzzle f <filename> <heuristic>" << std::endl;
    std::cerr << "       ./npuzzle g <field size> <heuristic>" << std::endl;
    exit(1);
}

std::string inputArgs(int ac, char **av) {
    if (ac == 4) {
        std::string flag(av[1]);

        if (flag == "f") {
            return flag;
        }
        if (flag == "g") {
            return flag;
        }
    }
    usage();
}

int main(int ac, char **av) {
    std::string flag;

    flag = inputArgs(ac, av);
    try {
        Parser parser(av, flag);
        Solver solver(parser.getField());
    }
    catch (Exceptions &e) {
        e.what();
    }
    return 0;
}