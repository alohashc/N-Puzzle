cmake_minimum_required(VERSION 3.13)
project(aloha_puzzle)

set(CMAKE_CXX_STANDARD 11)

add_executable(aloha_puzzle main.cpp Parser.cpp Parser.hpp NPuzzle.hpp Field.cpp Field.hpp Exceptions.cpp Exceptions.hpp Heuristics.cpp Heuristics.hpp Solver.cpp Solver.hpp)