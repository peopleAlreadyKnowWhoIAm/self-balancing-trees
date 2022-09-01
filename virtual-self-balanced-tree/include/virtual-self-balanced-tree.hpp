#pragma once

#include <string>

using std::string;



class VirtualSelfBalancedTree {
protected:

    struct Node {
        Node* ptr_left = nullptr;
        Node* ptr_right = nullptr;
        Node* ptr_parent = nullptr;
        int value;

        Node(const int value);
        ~Node();
        void DeleteWithoutChilds();

        virtual string ToString() const = 0;
    };

    void LeftLeftCase(Node* pChild);
    void LeftRightCase(Node* pChild);
    void RightLeftCase(Node* pChild);
    void RightRightCase(Node* pChild);

    void UpdateGreatgrandparent(Node* ptr_parent, Node* ptr_grandparent);

    //Return parent, where to paste or node itself, if was found
    //If pRoot is nullptr then use pRoot of the class
    Node* GoThrough(const int value, Node* ptr_root = nullptr) const;

    Node* ptr_root_ = nullptr;
public:
    ~VirtualSelfBalancedTree();

    virtual void Insert(const int) = 0;
    virtual void Remove(const int) = 0;

    //TODO rewrite
    string ToString() const;
};