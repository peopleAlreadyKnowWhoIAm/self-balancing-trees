#pragma once

#include "virtual-self-balanced-tree.hpp"

#include <iostream>

using std::cout, std::endl;

class AvlTree : public VirtualSelfBalancedTree {
private:
    struct AvlNode : public VirtualSelfBalancedTree::Node {
        int height = 1;

        string to_string() const;

        AvlNode(const int value);

        virtual ~AvlNode();
    };

    //`ptr_child` - inseted or will be deleted node
    void UpdateBalanceToRoot(AvlNode* ptr_child, bool inserted = true);

    //WARNING `ptr_node` must be AvlNode
    void UpdateBalanceForNode(Node* ptr_parent);

    //WARNING `ptr_node` must be AvlNode
    void Balance(Node* ptr_from, const int balance_factor);

    //WARNING `ptr_node` must be AvlNode
    int GetBalanceFactor(Node* ptr_parent) const;

    //WARNING `ptr_node` must be AvlNode
    int GetHeightFrom(Node* ptr_node) const;

    char const* GetType() const;
public:
    virtual ~AvlTree();

    void Insert(const int val);
    void Remove(const int val);
    
};
