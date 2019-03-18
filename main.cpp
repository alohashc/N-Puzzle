#include "Gen.hpp"
#include "Parser.hpp"

int main(int ac, char**av) {
//    Gen gen;
    std::string str(av[1]);

//    if grid generates by program
//    gen.Init();

    Parser parser;
    parser.run(str);

    return 0;
}