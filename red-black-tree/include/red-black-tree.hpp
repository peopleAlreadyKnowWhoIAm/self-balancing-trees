#pragma once

#include "virtual-self-balanced-tree.hpp"

#include <string>

using std::string, std::pair;

class RedBlackTree : public VirtualSelfBalancedTree {
    enum Color { red, black };

    struct RbNode : public VirtualSelfBalancedTree::Node {
        Color color = red;

        string to_string() const;

        RbNode(const int value);
        virtual ~RbNode();
    };



    void RedUncleCase(RbNode* ptr_child);

    //after iserting
    void balanceTree(RbNode* ptr_child);

    //after removing
    void rebalanceDBlackCase(RbNode* ptr_child);

    void recolor(RbNode* node, RbNode* from = nullptr);

    char const* GetType() const;

public:
    virtual ~RedBlackTree();

    void Insert(const int i);
    void Remove(const int i);


};