cmake_minimum_required(VERSION 3.10)


project(RedBlackTree)

add_library(RedBlackTree src/red-black-tree.cpp)
target_include_directories(RedBlackTree PUBLIC ${PROJECT_SOURCE_DIR}/include)