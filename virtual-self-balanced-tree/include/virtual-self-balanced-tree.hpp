#pragma once

#include <string>
#include <sstream>

using std::string, std::stringstream, std::endl;



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

        virtual string to_string() const = 0;
    };

    void LeftLeftCase(Node* ptr_child);
    void LeftRightCase(Node* ptr_child);
    void RightLeftCase(Node* ptr_child);
    void RightRightCase(Node* ptr_child);

    void UpdateParent(Node* ptr_parent, Node* ptr_grandparent);

    //Return parent, where to paste or node itself, if was found
    //If pRoot is nullptr then use pRoot of the class
    Node* GoThrough(const int value, Node* ptr_root = nullptr) const;

    Node* ptr_root_ = nullptr;

    stringstream to_string_(Node* root, int parent_value) const;

    virtual char const* GetType() const = 0;

private:
    void LeftRotation(Node* ptr_child);
    void RightRotation(Node* ptr_child);

public:
    ~VirtualSelfBalancedTree();

    virtual void Insert(const int) = 0;
    virtual void Remove(const int) = 0;

    string to_string() const;
};