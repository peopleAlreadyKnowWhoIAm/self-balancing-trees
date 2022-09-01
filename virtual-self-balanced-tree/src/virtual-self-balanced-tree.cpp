#include "virtual-self-balanced-tree.hpp"

VirtualSelfBalancedTree::Node::Node(const int value)
    :value(value) {}

VirtualSelfBalancedTree::Node::~Node() {
    if (ptr_right != nullptr) {
        delete ptr_right;
    }

    if (ptr_left != nullptr) {
        delete ptr_left;
    }
    ptr_parent = nullptr;

}

void VirtualSelfBalancedTree::Node::DeleteWithoutChilds() {
   ptr_right = nullptr;
   ptr_left = nullptr;
   delete this; 
}

VirtualSelfBalancedTree::~VirtualSelfBalancedTree() {
    delete ptr_root_;
}

void VirtualSelfBalancedTree::UpdateGreatgrandparent(Node* ptr_parent, Node* ptr_grandparent) {
    //Replace `Great-grandparent` pointer if exist
    if (ptr_grandparent->ptr_parent != nullptr) {
        Node* pGreatgrandparent = ptr_grandparent->ptr_parent;
        if (pGreatgrandparent->ptr_left == ptr_grandparent) {
            pGreatgrandparent->ptr_left = ptr_parent;
        }
        else {
            pGreatgrandparent->ptr_right = ptr_parent;
        }

        ptr_parent->ptr_parent = pGreatgrandparent;
    }
    else {
        ptr_root_ = ptr_parent;
        ptr_root_->ptr_parent = nullptr;
    }
}

void VirtualSelfBalancedTree::LeftLeftRot(Node* ptr_child) {

    Node* ptr_parent = ptr_child->ptr_parent;
    Node* pT3 = ptr_parent->ptr_right;
    Node* ptr_grandparent = ptr_parent->ptr_parent;

    UpdateGreatgrandparent(ptr_parent, ptr_grandparent);

    ptr_parent->ptr_right = ptr_grandparent;
    ptr_grandparent->ptr_parent = ptr_parent;

    ptr_grandparent->ptr_left = pT3;
    if (pT3 != nullptr) {
        pT3->ptr_parent = ptr_grandparent;
    }
}

void VirtualSelfBalancedTree::LeftRightRot(Node* ptr_child) {
    Node* pT2 = ptr_child->ptr_left;
    Node* ptr_parent = ptr_child->ptr_parent;
    Node* ptr_grandparent = ptr_parent->ptr_parent;

    //Prepare parent
    ptr_parent->ptr_right = pT2;
    if (pT2 != nullptr) {
        pT2->ptr_parent = ptr_parent;
    }
    ptr_parent->ptr_parent = ptr_child;

    //Prepare child
    ptr_child->ptr_left = ptr_parent;
    ptr_grandparent->ptr_left = ptr_child;
    ptr_child->ptr_parent = ptr_grandparent;

    LeftLeftRot(ptr_parent);
}

void VirtualSelfBalancedTree::RightRightRot(Node* ptr_child) {
    Node* ptr_parent = ptr_child->ptr_parent;
    Node* pT3 = ptr_parent->ptr_left;
    Node* ptr_grandparent = ptr_parent->ptr_parent;

    UpdateGreatgrandparent(ptr_parent, ptr_grandparent);

    //Prepare Parent
    ptr_parent->ptr_left = ptr_grandparent;
    ptr_grandparent->ptr_parent = ptr_parent;

    //Prepare Grandparent
    ptr_grandparent->ptr_right = pT3;
    if (pT3 != nullptr) {
        pT3->ptr_parent = ptr_grandparent;
    }
}

void VirtualSelfBalancedTree::RightLeftRot(Node* ptr_child) {
    Node* pT4 = ptr_child->ptr_right;
    Node* ptr_parent = ptr_child->ptr_parent;
    Node* ptr_grandparent = ptr_parent->ptr_parent;

    //Prepare parent
    ptr_parent->ptr_left = pT4;
    if (pT4 != nullptr) {
        pT4->ptr_parent = ptr_parent;
    }
    ptr_parent->ptr_parent = ptr_child;

    //Prepare child
    ptr_child->ptr_right = ptr_parent;
    ptr_grandparent->ptr_right = ptr_child;
    ptr_child->ptr_parent = ptr_grandparent;

    RightRightRot(ptr_parent);
}

VirtualSelfBalancedTree::Node* VirtualSelfBalancedTree::GoThrough(const int value, Node* ptr_root/* = nullptr*/) const {
    Node* ptr_parent = nullptr, * ptr_child = ptr_root;

    if (ptr_child == nullptr) {
        ptr_child = this->ptr_root_;
    }

    while (ptr_child != nullptr) {
        ptr_parent = ptr_child;

        if (ptr_parent->value == value) {
            break;
        }

        if (value > ptr_parent->value) {
            ptr_child = ptr_parent->ptr_right;
        }
        else {
            ptr_child = ptr_parent->ptr_left;
        }
    }

    return ptr_parent;
}