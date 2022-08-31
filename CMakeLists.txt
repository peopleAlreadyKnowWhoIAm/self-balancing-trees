cmake_minimum_required(VERSION 3.10)

project(RedBlackTreeExec)

add_subdirectory(red-black-tree)

add_executable(RedBlackTreeExec main.cpp)
target_link_libraries(RedBlackTreeExec RedBlackTree)