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
    ptr_parent = nullptr;
    delete this;
}

VirtualSelfBalancedTree::~VirtualSelfBalancedTree() {
    delete ptr_root_;
}

void VirtualSelfBalancedTree::UpdateParent(Node* ptr_new_child, Node* ptr_old_child) {
    //Replace `Great-grandparent` pointer if exist
    if (ptr_old_child->ptr_parent != nullptr) {
        Node* pGrandparent = ptr_old_child->ptr_parent;
        if (pGrandparent->ptr_left == ptr_old_child) {
            pGrandparent->ptr_left = ptr_new_child;
        }
        else {
            pGrandparent->ptr_right = ptr_new_child;
        }

        ptr_new_child->ptr_parent = pGrandparent;
    }
    else {
        ptr_root_ = ptr_new_child;
        ptr_root_->ptr_parent = nullptr;
    }
}

void VirtualSelfBalancedTree::LeftLeftCase(Node* ptr_child) {
    RightRotation(ptr_child->ptr_parent);

    // Node* ptr_parent = ptr_child->ptr_parent;
    // Node* pT3 = ptr_parent->ptr_right;
    // Node* ptr_grandparent = ptr_parent->ptr_parent;

    // UpdateParent(ptr_parent, ptr_grandparent);

    // ptr_parent->ptr_right = ptr_grandparent;
    // ptr_grandparent->ptr_parent = ptr_parent;

    // ptr_grandparent->ptr_left = pT3;
    // if (pT3 != nullptr) {
    //     pT3->ptr_parent = ptr_grandparent;
    // }
}

void VirtualSelfBalancedTree::LeftRightCase(Node* ptr_child) {
    LeftRotation(ptr_child);

    RightRotation(ptr_child);
}

void VirtualSelfBalancedTree::RightRightCase(Node* ptr_child) {
    LeftRotation(ptr_child->ptr_parent);
}

void VirtualSelfBalancedTree::RightLeftCase(Node* ptr_child) {
    RightRotation(ptr_child);

    LeftRotation(ptr_child);
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

stringstream VirtualSelfBalancedTree::to_string_(Node* ptr_parent, int parent_value) const {
    stringstream out;
    if (parent_value == __INT_MAX__) {
        out << GetType() << endl;
    }

    if (ptr_parent == nullptr) {
        ptr_parent = ptr_root_;
    }
    //Double check if tree is empty
    if (ptr_parent != nullptr) {
        out << ptr_parent->to_string();
        if (parent_value != __INT_MAX__) {
            out << " " << parent_value;
        }
        out << endl;

        parent_value = ptr_parent->value;
        if (ptr_parent->ptr_left != nullptr) {
            out << to_string_(ptr_parent->ptr_left, parent_value).str();
        }
        if (ptr_parent->ptr_right != nullptr) {
            out << to_string_(ptr_parent->ptr_right, parent_value).str();
        }
    }

    return out;
}

string VirtualSelfBalancedTree::to_string() const {
    stringstream out = to_string_(ptr_root_, __INT_MAX__);
    out << endl;
    return out.str();
}

void VirtualSelfBalancedTree::RightRotation(Node* ptr_child) {
    Node* ptr_parent = ptr_child->ptr_parent;
    Node* pT3 = ptr_child->ptr_right;

    UpdateParent(ptr_child, ptr_parent);

    //Update parent
    if (pT3 != nullptr) {
        pT3->ptr_parent = ptr_parent;
    }
    ptr_parent->ptr_left = pT3;

    //Update child
    ptr_child->ptr_right = ptr_parent;
    ptr_parent->ptr_parent = ptr_child;
}

void VirtualSelfBalancedTree::LeftRotation(Node* ptr_child) {
    Node* ptr_parent = ptr_child->ptr_parent;
    Node* pT3 = ptr_child->ptr_left;

    UpdateParent(ptr_child, ptr_parent);

    //Update parent
    if (pT3 != nullptr) {
        pT3->ptr_parent = ptr_parent;
    }
    ptr_parent->ptr_right = pT3;

    //Update child
    ptr_child->ptr_left = ptr_parent;
    ptr_parent->ptr_parent = ptr_child;
}