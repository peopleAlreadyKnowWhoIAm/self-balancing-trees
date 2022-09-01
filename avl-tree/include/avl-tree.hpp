#pragma once

#include "virtual-self-balanced-tree.hpp"

#include <iostream>

using std::cout, std::endl;

class AvlTree: public VirtualSelfBalancedTree
{
private:
    struct AvlNode: public VirtualSelfBalancedTree::Node {
        int height = 1;

        //TODO rewrite
        string ToString() const {return string(std::to_string(value) + ", " + std::to_string(height));}

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


public:
    virtual ~AvlTree();
    
    void Insert(const int val);
    void Remove(const int val);
    //TEMPORARY
    void writeout(AvlNode* root = nullptr) const{
        if(root == nullptr) {
            root = static_cast<AvlNode*>(ptr_root_);
        }
        cout<<root->ToString()<<endl;
        if(root->ptr_left != nullptr) {
            writeout(static_cast<AvlNode*>(root->ptr_left));
        }
        if(root->ptr_right != nullptr) {
            writeout(static_cast<AvlNode*>(root->ptr_right));
        }

    };
};
