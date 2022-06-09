cmake_minimum_required(VERSION 3.22)
project(RBTree)

set(CMAKE_CXX_STANDARD 14)

add_executable(RBTree main.cpp RBTree.cpp RBTree.h RBNode.cpp RBNode.h AVLtree.h AVLtree.cpp)
