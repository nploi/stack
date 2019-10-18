cmake_minimum_required(VERSION 3.9.2)
project(stacker)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

file(GLOB_RECURSE SOURCE main.cpp src/*.cpp)

add_custom_target(
	play
	COMMAND make && ./stacker
)

add_executable(stacker ${SOURCE})

install(TARGETS stacker RUNTIME DESTINATION bin)
