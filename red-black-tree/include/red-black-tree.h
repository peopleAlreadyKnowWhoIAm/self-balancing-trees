#pragma once

#include <string>

using std::string, std::pair;



class RedBlackTree {
    enum Color { red, black };

    struct Node {
        Color color = red;

        int value;

        Node* pParent = nullptr;
        Node* pLeft = nullptr;
        Node* pRight = nullptr;

        Node(int value) :value(value) {};
        void deleteWithoutChilds();
        ~Node();
    };

    Node* pRoot = nullptr;


    void LeftLeftRot(Node* pChild);
    void LeftRightRot(Node* pChild);
    void RightLeftRot(Node* pChild);
    void RightRightRot(Node* pChild);

    void RedUncleCase(Node* pChild);

    //after iserting
    void balanceTree(Node* pChild);
    
    //after removing
    void rebalanceDBlackCase(Node* pChild);

    void recolor(Node*node, Node *from = nullptr);

    //Return parent, where to paste or node itself, if was found
    //If pRoot is nullptr then use pRoot of the class
    Node* GoThrough(const int& value, Node* pRoot = nullptr) const;
public:

    void insert(const int& i);
    void remove(const int i);

    string& to_string();


};