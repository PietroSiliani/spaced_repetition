cmake_minimum_required(VERSION 3.24)
project(spaced_repetition)

set(CMAKE_CXX_STANDARD 17)

add_executable(spaced_repetition main.cpp Subject.cpp Subject.h const.h DateNode.cpp DateNode.h)
