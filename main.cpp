#include "Parser.hpp"
#include "Solver.hpp"

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

    std::stringstream ss;
    ss << "Usage: ./npuzzle <flag: 'f'=file or 'g'=generate>" << std::endl;
    ss << "       ./npuzzle f <filename> <heuristic>" << std::endl;
    ss << "       ./npuzzle g <field size> <heuristic>" << std::endl;
    throw ss.str();
}

int main(int ac, char **av) {
    std::string flag;

    try {
        flag = inputArgs(ac, av);
        Parser parser(av, flag);
        Solver solver(parser.getField());
    }
    catch (const char *ex) {
        std::cout << ex << std::endl;
    }
    catch (const std::string &ex) {
        std::cout << ex << std::endl;
    }
    catch (const Exceptions &e) {
        e.what();
    }
//    catch (const std::exception &ex) {
//        std::cout << ex.what() << std::endl;
//    }
    return 0;
}