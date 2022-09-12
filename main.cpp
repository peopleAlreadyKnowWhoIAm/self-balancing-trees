#include "red-black-tree.hpp"
#include "avl-tree.hpp"
#include <vector>

#include <iostream>

using std::vector, std::cout, std::endl, std::cin;

int main() {
    vector a = {
       32, 97, 67, 36, 5, 70, 6, 42, 75, 43, 79, 49, 81, 51, 56, 93
    };
    RedBlackTree tree;

    for (auto i : a) {
        tree.Insert(i);
    }

    cout << tree.to_string();

    tree.Remove(49);
    cout << tree.to_string();

    tree.Remove(42);
    tree.Remove(81);
    tree.Remove(67);
    cout << tree.to_string();
    tree.Remove(70);
    tree.Remove(75);
    tree.Remove(97);
    cout << tree.to_string();
    tree.Remove(51);
    tree.Remove(6);
    tree.Remove(43);
    cout << tree.to_string();
    tree.Remove(5);
    tree.Remove(32);
    cout << tree.to_string();
    tree.Remove(93);
    tree.Remove(56);
    cout << tree.to_string();
    tree.Remove(36);
    cout << tree.to_string();
    tree.Remove(79);

    AvlTree atree;

    for (auto&& i : a) {
        atree.Insert(i);
        cout << atree.to_string();
    }

    atree.Remove(49);
    cout << atree.to_string();

    atree.Remove(42);
    atree.Remove(81);
    atree.Remove(67);
    cout << atree.to_string();
    atree.Remove(70);
    atree.Remove(75);
    atree.Remove(97);
    cout << atree.to_string();
    atree.Remove(51);
    atree.Remove(6);
    atree.Remove(43);
    cout << atree.to_string();
    atree.Remove(5);
    atree.Remove(32);
    cout << atree.to_string();
    atree.Remove(93);
    atree.Remove(56);
    cout << atree.to_string();
    atree.Remove(36);
    cout << atree.to_string();
    atree.Remove(79);

    return 0;
}