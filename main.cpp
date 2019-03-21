#include "Gen.hpp"
#include "Parser.hpp"

int main(int ac, char**av) {
    try {
        Parser parser;
        parser.run(av);
    }
    catch (Exceptions &e) {
        e.what();
    }
    return 0;
}