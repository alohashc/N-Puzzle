//
// Created by aloha on 21.03.19.
//

#include "Exceptions.hpp"

Exceptions::Exceptions() : std::exception() {

}

Exceptions::Exceptions(std::string &str) {
    this->msg = str;
}


Exceptions::~Exceptions() throw() {

}

char const* Exceptions::what() const throw() {
    std::cerr << this->msg << std::endl;
}