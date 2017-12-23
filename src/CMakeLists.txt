cmake_minimum_required(VERSION 3.0)
project(xSearch)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -O3 -Wall -Wextra")

add_executable(xSearch
	main.cpp
	searchengine.cpp
	searchengine.h)