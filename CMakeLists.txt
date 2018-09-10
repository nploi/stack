cmake_minimum_required(VERSION 3.10)
project(Stack)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

file(GLOB_RECURSE SOURCE main.cpp block.cpp util.cpp game.cpp)
add_executable(Stack ${SOURCE})
