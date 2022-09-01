cmake_minimum_required(VERSION 3.10)

project(VirtualSelfBalancedTree)

add_library(VirtualSelfBalancedTree STATIC src/virtual-self-balanced-tree.cpp include/virtual-self-balanced-tree.hpp)
target_include_directories(VirtualSelfBalancedTree BEFORE PUBLIC ${PROJECT_SOURCE_DIR}/include)
