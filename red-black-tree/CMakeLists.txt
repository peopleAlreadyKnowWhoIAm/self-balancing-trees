cmake_minimum_required(VERSION 3.10)


project(RedBlackTree)


add_library(RedBlackTree STATIC src/red-black-tree.cpp include/red-black-tree.hpp)
target_include_directories(RedBlackTree 
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    )
target_link_libraries(RedBlackTree VirtualSelfBalancedTree)
