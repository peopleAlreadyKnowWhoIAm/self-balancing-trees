#include "red-black-tree.h"
#include <vector>

#include <iostream>

using std::vector, std::cout, std::endl;

int main() {
    vector a = { 
       32, 97, 67, 36, 5, 70, 6, 42, 75, 43, 79, 49, 81, 51, 56, 93 
    };
    RedBlackTree tree;

    for (auto i : a) {
        cout<<i<<endl;
        tree.insert(i);
    }

    tree.remove(49);

    tree.remove(42);

    tree.remove(81);

    tree.remove(67);

    tree.remove(70);

    tree.remove(75);

    tree.remove(97);

    tree.remove(51);

    tree.remove(6);

    tree.remove(43);

    tree.remove(5);

    tree.remove(32);

    tree.remove(93);

    tree.remove(56);

    tree.remove(36);

    tree.remove(79);

    for(auto &&i: a) {
        tree.insert(i);
    }

    std::cout<<"It works"<<std::endl;

    return 0;
}