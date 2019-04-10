//
// Created by aloha on 21.03.19.
//

#ifndef ALOHA_PUZZLE_EXCEPTIONS_HPP
#define ALOHA_PUZZLE_EXCEPTIONS_HPP

#include <exception>
#include <iostream>

class Exceptions : public std::exception{
public:
    Exceptions();
    Exceptions(const std::string &);
    ~Exceptions() throw();

    virtual char const* what() const throw();
private:
    std::string msg;
};


#endif //ALOHA_PUZZLE_EXCEPTIONS_HPP
