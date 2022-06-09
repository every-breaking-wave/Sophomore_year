cmake_minimum_required(VERSION 3.22)
project(TopoSort)

set(CMAKE_CXX_STANDARD 14)

add_executable(TopoSort main.cpp Graph.cpp Graph.h)
