#include "red-black-tree.h"

void RedBlackTree::LeftLeftRot(Node* pChild) {
    Node* pParent = pChild->pParent;
    Node* pT3 = pParent->pRight;
    Node* pGrandparent = pParent->pParent;

    //Replace `Great-grandparent` pointer if exist
    if (pGrandparent->pParent != nullptr) {
        Node* pGreatgrandparent = pGrandparent->pParent;
        if (pGreatgrandparent->pLeft == pGrandparent) {
            pGreatgrandparent->pLeft = pParent;
        }
        else {
            pGreatgrandparent->pRight = pParent;
        }

        pParent->pParent = pGreatgrandparent;
    }
    else {
        pRoot = pParent;
        pRoot->pParent = nullptr;
    }

    pParent->pRight = pGrandparent;
    pGrandparent->pParent = pParent;
    pParent->color = black;

    pGrandparent->pLeft = pT3;
    if (pT3 != nullptr) {
        pT3->pParent = pGrandparent;
    }
    pGrandparent->color = red;

}

void RedBlackTree::LeftRightRot(Node* pChild) {
    Node* pT2 = pChild->pLeft;
    Node* pParent = pChild->pParent;
    Node* pGrandparent = pParent->pParent;

    //Prepare parent
    pParent->pRight = pT2;
    if (pT2 != nullptr) {
        pT2->pParent = pParent;
    }
    pParent->pParent = pChild;

    //Prepare child
    pChild->pLeft = pParent;
    pGrandparent->pLeft = pChild;
    pChild->pParent = pGrandparent;

    LeftLeftRot(pParent);
}

void RedBlackTree::RightRightRot(Node* pChild) {
    Node* pParent = pChild->pParent;
    Node* pT3 = pParent->pLeft;
    Node* pGrandparent = pParent->pParent;

    //Replace `Great-grandparent` pointer if exist
    if (pGrandparent->pParent != nullptr) {
        Node* pGreatgrandparent = pGrandparent->pParent;
        if (pGreatgrandparent->pLeft == pGrandparent) {
            pGreatgrandparent->pLeft = pParent;
        }
        else {
            pGreatgrandparent->pRight = pParent;
        }

        pParent->pParent = pGreatgrandparent;
    }
    else {
        pRoot = pParent;
        pRoot->pParent = nullptr;
    }

    //Prepare Parent
    pParent->pLeft = pGrandparent;
    pGrandparent->pParent = pParent;
    pParent->color = black;

    //Prepare Grandparent
    pGrandparent->pRight = pT3;
    if (pT3 != nullptr) {
        pT3->pParent = pGrandparent;
    }

    pGrandparent->color = red;
}

void RedBlackTree::RightLeftRot(Node* pChild) {
    Node* pT4 = pChild->pRight;
    Node* pParent = pChild->pParent;
    Node* pGrandparent = pParent->pParent;

    //Prepare parent
    pParent->pLeft = pT4;
    if (pT4 != nullptr) {
        pT4->pParent = pParent;
    }
    pParent->pParent = pChild;

    //Prepare child
    pChild->pRight = pParent;
    pGrandparent->pRight = pChild;
    pChild->pParent = pGrandparent;

    RightRightRot(pParent);
}

void RedBlackTree::RedUncleCase(Node* pChild) {
    Node* pParent = pChild->pParent;
    pParent->color = black;
    Node* pGrandparent = pParent->pParent;
    if (pGrandparent != pRoot)
        pGrandparent->color = red;

    //Uncle could be right or left depends which parent is
    if (pGrandparent->pLeft == pParent) {
        pGrandparent->pRight->color = black;
    }
    else {
        pGrandparent->pLeft->color = black;
    }

    //If grandparents has 2 ancestors maybe
    if (pGrandparent->pParent != nullptr && pGrandparent->pParent->pParent != nullptr) {
        balanceTree(pGrandparent);
    }

}

RedBlackTree::Node::~Node() {
    delete pLeft;
    delete pRight;
}

void RedBlackTree::Node::deleteWithoutChilds() {
    pLeft = nullptr;
    pRight = nullptr;
    delete this;
}

void RedBlackTree::insert(const int& value) {
    Node* pChild = new Node(value);
    Node* pParent = GoThrough(value);

    //Only if there are not the value in the tree
    if (pParent == nullptr || pParent->value != value) {

        //It not depends from position
        pChild->pParent = pParent;

        //RootNode
        if (pParent == nullptr) {
            pChild->color = black;
            pRoot = pChild;
        }
        else {

            //Paste child in parent
            if (value > pParent->value) {
                pParent->pRight = pChild;
            }
            else {
                pParent->pLeft = pChild;
            }

            balanceTree(pChild);
        }

    }
}

void RedBlackTree::balanceTree(Node* pChild) {
    Node* pParent = pChild->pParent;
    if (pParent != nullptr) {
        Node* pGrandparent = pParent->pParent;


        //if parent isn't root or parent are black there nothing to do 
        if (pGrandparent != nullptr && pParent->color == red) {
            int uncleColor;
            //If uncle exist else black
            if (pGrandparent->pLeft == pParent) {
                Node* pUncle = pGrandparent->pRight;
                if (pUncle == nullptr) {
                    uncleColor = black;
                }
                else {
                    uncleColor = pUncle->color;
                }
            }
            else {
                Node* pUncle = pGrandparent->pLeft;
                if (pUncle == nullptr) {
                    uncleColor = black;
                }
                else {
                    uncleColor = pUncle->color;
                }
            }

            if (uncleColor == red) {
                RedUncleCase(pChild);
            }
            else {

                //Locate child relative parent and grandparent
                bool isChildRightParent = (pParent->pRight == pChild);

                bool isParentRightGrandparent = (pGrandparent->pRight == pParent);

                if (isParentRightGrandparent) {
                    if (isChildRightParent) {
                        RightRightRot(pChild);
                    }
                    else {
                        RightLeftRot(pChild);
                    }
                }
                else {
                    if (isChildRightParent) {
                        LeftRightRot(pChild);
                    }
                    else {
                        LeftLeftRot(pChild);
                    }
                }

            }
        }
    }
}

RedBlackTree::Node* RedBlackTree::GoThrough(const int& value, Node* pRoot/* = nullptr*/) const {
    Node* pParent = nullptr, * pChild = pRoot;

    if (pChild == nullptr) {
        pChild = this->pRoot;
    }

    while (pChild != nullptr) {
        pParent = pChild;

        if (pParent->value == value) {
            break;
        }

        if (value > pParent->value) {
            pChild = pParent->pRight;
        }
        else {
            pChild = pParent->pLeft;
        }
    }

    return pParent;
}


void RedBlackTree::remove(const int value) {
    Node* pDelete = GoThrough(value);
    //If nullptr there aren't this value in the tree
    if (pDelete != nullptr) {

        //Find replacement and replace
        //If not a single child
        if (pDelete->pRight != nullptr && pDelete->pLeft != nullptr) {
            Node* pToPaste = GoThrough(pDelete->value, pDelete->pLeft);
            pDelete->value = pToPaste->value;

            //Update node to delete
            //Because we copied from here value
            pDelete = pToPaste;
        }

        //explore case
        //parent - node to delete
        int parentColor = pDelete->color;
        int reddestChildColor = black;
        Node* pChild = nullptr, * pParent = pDelete;
        bool isChildRight;
        if (pParent->pLeft != nullptr) {
            pChild = pParent->pLeft;
            isChildRight = false;
            reddestChildColor = pChild->color;
        }
        else if (pParent->pRight != nullptr) {
            pChild = pParent->pRight;
            isChildRight = true;
            reddestChildColor = pChild->color;
        }

        //Edge case
        if(pRoot = pDelete){
            pRoot = nullptr;
        } else
        //Case 1
        //Parent or child are red
        if (reddestChildColor == red || parentColor == red) {
            pChild->color = black;
            //If parent root
            if (pParent->pParent == nullptr) {
                pChild->pParent = nullptr;
                pRoot = pChild;

            }
            else {
                Node* pGrandparent = pParent->pParent;
                bool isRightParent = (pGrandparent->pRight == pParent);


                //Exclude parent from tree
                pChild->pParent = pGrandparent;
                if (isRightParent) {
                    pGrandparent->pRight = pChild;
                }
                else {
                    pGrandparent->pLeft = pChild;
                }

            }

        }
        else {
            bool isParentRight = (pParent->pParent->pRight == pParent);
            

            rebalanceDBlackCase(pParent);

            if (isParentRight) {
                pParent->pParent->pRight = nullptr;
            }
            else {
                pParent->pParent->pLeft = nullptr;
            }

            pRoot->color = Color::black;
        }
        pParent->deleteWithoutChilds();
    }
}

void RedBlackTree::rebalanceDBlackCase(Node* pParent) {
    //Child and parent was black
    //Parent - double black

    //And always has null children
    Node* pGrandparent = pParent->pParent;
    if(pGrandparent == nullptr) {
        pParent->color = Color::black;
        return;
    }


    //Grandparent rigth or left is double black
    Node* pSibling;

    bool isSiblingRight = pGrandparent->pRight != pParent;


    if (isSiblingRight) {
        pSibling = pGrandparent->pRight;
    }
    else {
        pSibling = pGrandparent->pLeft;
    }



    //Case 2 and 3 sibling are black
    if (pSibling == nullptr || pSibling->color == black) {
        int reddestSiblingChildrenColor = black;
        bool isReddestChildrenRight;
        Node* pSiblingRedChild = nullptr;

        if (pSibling != nullptr) {
            if (pSibling->pRight != nullptr && pSibling->pRight->color == red) {
                isReddestChildrenRight = true;
                pSiblingRedChild = pSibling->pRight;
            }
            else if (pSibling->pLeft != nullptr && pSibling->pLeft->color == red) {
                isReddestChildrenRight = false;
                pSiblingRedChild = pSibling->pLeft;
            }
        }

        //Case 2
        //Needs rotation
        if (pSiblingRedChild != nullptr) {

            if (isSiblingRight) {
                if (isReddestChildrenRight) {
                    RightRightRot(pSiblingRedChild);
                }
                else {
                    RightLeftRot(pSiblingRedChild);
                    pSibling = pSiblingRedChild;

                }
            }
            else {
                if (isReddestChildrenRight) {
                    LeftRightRot(pSiblingRedChild);
                    pSibling = pSiblingRedChild;
                }
                else {
                    LeftLeftRot(pSiblingRedChild);
                }
            }

            if (pSibling->pLeft != nullptr) {
                pSibling->pLeft->color = black;
            }
            if (pSibling->pRight != nullptr) {
                pSibling->pRight->color = black;
            }
            pSibling->color = Color::red;

        }
        //Case 3 recoloring
        else {
            recolor(pGrandparent, pParent);
        }


    }
    //Case 4 Sibling is red
    else {
        if (isSiblingRight) {
            RightRightRot(pSibling->pRight);
        }
        else {
            LeftLeftRot(pSibling->pLeft);
        }
        recolor(pGrandparent, pParent);
    }

}




void RedBlackTree::recolor(Node* node, Node* from /*= nullptr*/) {
        if (from != nullptr) {

            //Paint sibling red
            //They must be black
            if (node->pLeft == from && node->pRight != nullptr) {
                node->pRight -> color = Color::red;
            }
            else if (node->pRight == from && node->pLeft != nullptr) {
                node->pLeft -> color = Color::red;
            }
        }

        if (node->color == black) {
            //Relative the node will be working with node parent
            rebalanceDBlackCase(node);
        }
        else {
            node->color = black;
        }
    }