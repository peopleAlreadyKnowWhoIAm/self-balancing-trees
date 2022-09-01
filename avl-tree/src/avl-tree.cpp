#include "avl-tree.hpp"

#include<algorithm>

#include<iostream>

using std::max, std::cout, std::endl;

AvlTree::AvlNode::AvlNode(const int value)
    : Node(value) {}

AvlTree::AvlNode::~AvlNode() {}

AvlTree::~AvlTree() {}


void AvlTree::UpdateBalanceToRoot(AvlNode* ptr_child, bool inserted) {
    AvlNode* ptr_parent = static_cast<AvlNode*>(ptr_child->ptr_parent);
    int difference_value = (inserted) ? 1 : -1;
    while (ptr_parent != nullptr) {
        Node* buf_ptr_parent = ptr_parent->ptr_parent;
        UpdateBalanceForNode(ptr_parent);
        ptr_parent = static_cast<AvlNode*>(buf_ptr_parent);
    }

}

void AvlTree::UpdateBalanceForNode(Node* ptr_parent) {
    int balance_factor = GetBalanceFactor(ptr_parent);

    if (balance_factor > 1 || balance_factor < -1) {
        Balance(ptr_parent, balance_factor);
    }
    else {
        static_cast<AvlNode*>(ptr_parent)->height = max(
            GetHeightFrom(ptr_parent->ptr_left),
            GetHeightFrom(ptr_parent->ptr_right)) + 1;
    }
}

void AvlTree::Balance(Node* ptr_from, const int balance_factor) {
    //Left child is taller
    //Left case    
    if (balance_factor > 0) {
        if (GetBalanceFactor(ptr_from->ptr_left) > 0) {
            LeftLeftCase(ptr_from->ptr_left->ptr_left);
            UpdateBalanceForNode(ptr_from);
            UpdateBalanceForNode(ptr_from->ptr_parent);
        }
        else {
            Node* ptr_parent = ptr_from->ptr_left;
            Node* ptr_child = ptr_parent->ptr_right;
            LeftRightCase(ptr_child);
            UpdateBalanceForNode(ptr_parent);
            UpdateBalanceForNode(ptr_from);
            UpdateBalanceForNode(ptr_child);
        }
    }
    //Rigth case
    else {
        if (GetBalanceFactor(ptr_from->ptr_right) > 0) {
            Node* ptr_parent = ptr_from->ptr_right;
            Node* ptr_child = ptr_parent->ptr_left;
            RightLeftCase(ptr_child);
            UpdateBalanceForNode(ptr_parent);
            UpdateBalanceForNode(ptr_from);
            UpdateBalanceForNode(ptr_child);

        }
        else {
            RightRightCase(ptr_from->ptr_right->ptr_right);
            UpdateBalanceForNode(ptr_from);
            //Becomes upper node
            UpdateBalanceForNode(ptr_from->ptr_parent);
        }

    }
}


int AvlTree::GetBalanceFactor(Node* ptr_parent) const {
    int left_height = GetHeightFrom(ptr_parent->ptr_left);
    int right_height = GetHeightFrom(ptr_parent->ptr_right);
    return left_height - right_height;
}

int AvlTree::GetHeightFrom(Node* ptr_node) const {
    AvlNode* _ptr_node = static_cast<AvlNode*>(ptr_node);
    int height = 0;
    if (_ptr_node != nullptr) {
        height = _ptr_node->height;
    }
    return height;
}

void AvlTree::Insert(const int value) {
    AvlNode* ptr_child = new AvlNode(value);
    AvlNode* ptr_parent = static_cast<AvlNode*>(GoThrough(value));

    //Check presence of ned with the same value
    if (ptr_parent == nullptr || ptr_parent->value != value) {

        //It not depends from position
        //Could be root
        ptr_child->ptr_parent = ptr_parent;

        //RootNode  case
        if (ptr_parent == nullptr) {
            cout << "Inserted as root val: " << ptr_child << endl;
            ptr_root_ = ptr_child;
        }
        else {
            //Paste child in parent
            if (value > ptr_parent->value) {
                ptr_parent->ptr_right = ptr_child;
            }
            else {
                ptr_parent->ptr_left = ptr_child;
            }

            UpdateBalanceToRoot(ptr_child);
        }
    }

}

void AvlTree::Remove(const int value) {

    AvlNode* ptr_delete = static_cast<AvlNode*>(GoThrough(value));
    //If nullptr there aren't this value in the tree
    if (ptr_delete != nullptr) {

        //Find replacement and replace
        //If not a single child
        if (ptr_delete->ptr_right != nullptr && ptr_delete->ptr_left != nullptr) {
            AvlNode* ptr_to_paste = static_cast<AvlNode*>(GoThrough(ptr_delete->value, ptr_delete->ptr_left));
            ptr_delete->value = ptr_to_paste->value;

            //Update node to delete
            //Because we copied from here value
            ptr_delete = ptr_to_paste;
        }
        //Edge case
        if (ptr_root_ == ptr_delete && ptr_root_->ptr_left == nullptr && ptr_root_->ptr_right == nullptr) {
            ptr_root_ = nullptr;
        }

        //As for binary tree ptr_delete must have at most 1 child
        Node* ptr_delete_child;
        if (ptr_delete->ptr_right != nullptr) {
            ptr_delete_child = ptr_delete->ptr_right;
        }
        else {
            //Even if left child absent the variable will be asigned `nullptr`
            ptr_delete_child = ptr_delete->ptr_left;
        }

        Node* ptr_delete_parent = ptr_delete->ptr_parent;
        if (ptr_delete_parent == nullptr) {
            ptr_root_ = ptr_delete_child;
        }
        else {
            bool is_delete_node_right = (ptr_delete_parent->ptr_right == ptr_delete);
            if (is_delete_node_right) {
                ptr_delete_parent->ptr_right = ptr_delete_child;
            }
            else {
                ptr_delete_parent->ptr_left = ptr_delete_child;
            }

            if (ptr_delete_child != nullptr) {
                ptr_delete_child->ptr_parent = ptr_delete_parent;
            }

            ptr_delete->height = 0;

            UpdateBalanceToRoot(static_cast<AvlNode*>(ptr_delete));
        }
        ptr_delete->DeleteWithoutChilds();
    }
}
