cmake_minimum_required(VERSION 3.13)
project(aloha_puzzle)

set(CMAKE_CXX_STANDARD 11)

add_executable(aloha_puzzle main.cpp Gen.cpp Gen.hpp State.cpp State.hpp Grid.cpp Grid.hpp Parser.cpp Parser.hpp)