//
// Created by aloha on 21.03.19.
//

#include "Exceptions.hpp"

Exceptions::Exceptions() : std::exception() {

}

Exceptions::Exceptions(const std::string &str) {
    msg = str;
}


Exceptions::~Exceptions() throw() {

}

char const* Exceptions::what() const throw() {
    std::cerr << msg << std::endl;
}