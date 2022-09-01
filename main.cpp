#include "red-black-tree.hpp"
#include "avl-tree.hpp"
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
        tree.Insert(i);
    }

    tree.Remove(49);

    tree.Remove(42);
    tree.Remove(81);
    tree.Remove(67);
    tree.Remove(70);
    tree.Remove(75);
    tree.Remove(97);
    tree.Remove(51);
    tree.Remove(6);
    tree.Remove(43);
    tree.Remove(5);
    tree.Remove(32);
    tree.Remove(93);
    tree.Remove(56);
    tree.Remove(36);
    tree.Remove(79);

    AvlTree atree;

    for(auto &&i: a) {
             atree.Insert(i);
    }
    atree.writeout();
    atree.Remove(49);
    atree.Remove(42);
    atree.Remove(81);
    atree.writeout();
    atree.Remove(67);
    atree.writeout();
    atree.Remove(70);
    atree.writeout();
    atree.Remove(75);
    atree.writeout();
    atree.Remove(97);
    atree.writeout();
    atree.Remove(51);
    atree.writeout();
    atree.Remove(6);
    atree.writeout();
    atree.Remove(43);
    atree.writeout();
    atree.Remove(5);
    atree.writeout();
    atree.Remove(32);
    atree.writeout();
    atree.Remove(93);
    atree.writeout();
    atree.Remove(56);
    atree.writeout();
    atree.Remove(36);
    atree.writeout();
    atree.Remove(79);
    atree.writeout();

    std::cout<<"It works"<<std::endl;

    return 0;
}