cmake_minimum_required(VERSION 3.10)

set(CMAKE_BUILD_TYPE Debug)

project(RedBlackTreeExec)

add_subdirectory(virtual-self-balanced-tree)
add_subdirectory(red-black-tree)

add_executable(RedBlackTreeExec main.cpp)
target_link_libraries(RedBlackTreeExec RedBlackTree)