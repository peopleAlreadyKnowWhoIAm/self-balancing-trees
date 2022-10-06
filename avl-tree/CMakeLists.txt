cmake_minimum_required(VERSION 3.10)

project(AVLTree)

add_library(AVLTree STATIC src/avl-tree.cpp include/avl-tree.hpp)
target_include_directories(AVLTree 
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    )
target_link_libraries(AVLTree VirtualSelfBalancedTree)