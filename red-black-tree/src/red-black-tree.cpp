#include "red-black-tree.hpp"

RedBlackTree::RbNode::RbNode(const int value)
    :Node(value) {}

RedBlackTree::RbNode::~RbNode() {}

string RedBlackTree::RbNode::to_string() const {
    const char* color = (this->color == Color::red)?"red":"black";
    return string(std::to_string(this->value) + ' ' + color);
}

RedBlackTree::~RedBlackTree() {}

void RedBlackTree::RedUncleCase(RbNode* ptr_child) {
    RbNode* ptr_parent = static_cast<RbNode*>(ptr_child->ptr_parent);
    ptr_parent->color = black;
    RbNode* ptr_grandparent = static_cast<RbNode*>(ptr_parent->ptr_parent);
    if (ptr_grandparent != ptr_root_)
        ptr_grandparent->color = red;

    //Uncle could be right or left depends which parent is
    if (ptr_grandparent->ptr_left == ptr_parent) {
        static_cast<RbNode*>(ptr_grandparent->ptr_right)->color = black;
    }
    else {
        static_cast<RbNode*>(ptr_grandparent->ptr_left)->color = black;
    }

    //If grandparents has 2 ancestors maybe
    if (ptr_grandparent->ptr_parent != nullptr && ptr_grandparent->ptr_parent->ptr_parent != nullptr) {
        balanceTree(ptr_grandparent);
    }

}


void RedBlackTree::Insert(const int value) {
    RbNode* ptr_child = new RbNode(value);
    RbNode* ptr_parent = static_cast<RbNode*>(GoThrough(value));

    //Only if there are not the value in the tree
    if (ptr_parent == nullptr || ptr_parent->value != value) {

        //It not depends from position
        //Could be root
        ptr_child->ptr_parent = ptr_parent;

        //RootNode  case
        if (ptr_parent == nullptr) {
            ptr_child->color = black;
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

            balanceTree(ptr_child);
        }

    }
}

void RedBlackTree::balanceTree(RbNode* ptr_child) {
    RbNode* ptr_parent = static_cast<RbNode*>(ptr_child->ptr_parent);
    if (ptr_parent != nullptr) {
        RbNode* ptr_grandparent = static_cast<RbNode*>(ptr_parent->ptr_parent);


        //if parent isn't root or parent are black there nothing to do 
        if (ptr_grandparent != nullptr && ptr_parent->color == red) {
            int uncleColor;
            //If uncle exist else black
            if (ptr_grandparent->ptr_left == ptr_parent) {
                RbNode* pUncle = static_cast<RbNode*>(ptr_grandparent->ptr_right);
                if (pUncle == nullptr) {
                    uncleColor = black;
                }
                else {
                    uncleColor = pUncle->color;
                }
            }
            else {
                RbNode* pUncle = static_cast<RbNode*>(ptr_grandparent->ptr_left);
                if (pUncle == nullptr) {
                    uncleColor = black;
                }
                else {
                    uncleColor = pUncle->color;
                }
            }

            if (uncleColor == red) {
                RedUncleCase(ptr_child);
            }
            else {

                //Locate child relative parent and grandparent
                bool isChildRightParent = (ptr_parent->ptr_right == ptr_child);

                bool isParentRightGrandparent = (ptr_grandparent->ptr_right == ptr_parent);

                if (isParentRightGrandparent) {
                    if (isChildRightParent) {
                        RightRightCase(ptr_child);
                        ptr_grandparent->color = red;
                        ptr_parent->color = black;
                    }
                    else {
                        RightLeftCase(ptr_child);
                        ptr_grandparent->color = red;
                        ptr_child->color = black;
                    }
                }
                else {
                    if (isChildRightParent) {
                        LeftRightCase(ptr_child);
                        ptr_grandparent->color = red;
                        ptr_child->color = black;
                    }
                    else {
                        LeftLeftCase(ptr_child);
                        ptr_grandparent->color = red;
                        ptr_parent->color = black;
                    }

                }


            }
        }
    }
}


void RedBlackTree::Remove(const int value) {
    RbNode* ptr_delete = static_cast<RbNode*>(GoThrough(value));
    //If nullptr there aren't this value in the tree
    if (ptr_delete != nullptr) {

        //Find replacement and replace
        //If not a single child
        if (ptr_delete->ptr_right != nullptr && ptr_delete->ptr_left != nullptr) {
            RbNode* ptr_to_paste = static_cast<RbNode*>(GoThrough(ptr_delete->value, ptr_delete->ptr_left));
            ptr_delete->value = ptr_to_paste->value;

            //Update node to delete
            //Because we copied from here value
            ptr_delete = ptr_to_paste;
        }

        //explore case
        //parent - node to delete
        int parentColor = ptr_delete->color;
        int reddestChildColor = black;
        RbNode* ptr_child = nullptr, * ptr_parent = ptr_delete;
        bool isChildRight;
        if (ptr_parent->ptr_left != nullptr) {
            ptr_child = static_cast<RbNode*>(ptr_parent->ptr_left);
            isChildRight = false;
            reddestChildColor = ptr_child->color;
        }
        else if (ptr_parent->ptr_right != nullptr) {
            ptr_child = static_cast<RbNode*>(ptr_parent->ptr_right);
            isChildRight = true;
            reddestChildColor = ptr_child->color;
        }

        //Edge case
        if (ptr_root_ == ptr_delete && ptr_root_ ->ptr_left == nullptr && ptr_root_ -> ptr_right == nullptr) {
            ptr_root_ = nullptr;
        }
        else
            //Case 1
            //Parent or child are red
            if (reddestChildColor == red || parentColor == red) {
                ptr_child->color = black;
                //If parent root
                if (ptr_parent->ptr_parent == nullptr) {
                    ptr_child->ptr_parent = nullptr;
                    ptr_root_ = ptr_child;

                }
                else {
                    Node* ptr_grandparent = ptr_parent->ptr_parent;
                    bool isRightParent = (ptr_grandparent->ptr_right == ptr_parent);


                    //Exclude parent from tree
                    ptr_child->ptr_parent = ptr_grandparent;
                    if (isRightParent) {
                        ptr_grandparent->ptr_right = ptr_child;
                    }
                    else {
                        ptr_grandparent->ptr_left = ptr_child;
                    }

                }

            }
            else {
                bool isParentRight = (ptr_parent->ptr_parent->ptr_right == ptr_parent);


                rebalanceDBlackCase(ptr_parent);

                if (isParentRight) {
                    ptr_parent->ptr_parent->ptr_right = nullptr;
                }
                else {
                    ptr_parent->ptr_parent->ptr_left = nullptr;
                }

                static_cast<RbNode*>(ptr_root_)->color = Color::black;
            }
        ptr_parent->DeleteWithoutChilds();
    }
}

void RedBlackTree::rebalanceDBlackCase(RbNode* ptr_parent) {
    //Child and parent was black
    //Parent - double black

    //And always has null children
    RbNode* ptr_grandparent = static_cast<RbNode*>(ptr_parent->ptr_parent);
    if (ptr_grandparent == nullptr) {
        ptr_parent->color = Color::black;
        return;
    }


    //Grandparent rigth or left is double black
    RbNode* ptr_sibling;

    bool isSiblingRight = ptr_grandparent->ptr_right != ptr_parent;


    if (isSiblingRight) {
        ptr_sibling = static_cast<RbNode*>(ptr_grandparent->ptr_right);
    }
    else {
        ptr_sibling = static_cast<RbNode*>(ptr_grandparent->ptr_left);
    }



    //Case 2 and 3 sibling are black
    if (ptr_sibling == nullptr || ptr_sibling->color == black) {
        int reddestSiblingChildrenColor = black;
        bool isReddestChildrenRight;
        RbNode* ptr_siblings_red_child = nullptr;

        if (ptr_sibling != nullptr) {
            if (ptr_sibling->ptr_right != nullptr && static_cast<RbNode*>(ptr_sibling->ptr_right)->color == red) {
                isReddestChildrenRight = true;
                ptr_siblings_red_child = static_cast<RbNode*>(ptr_sibling->ptr_right);
            }
            else if (ptr_sibling->ptr_left != nullptr && static_cast<RbNode*>(ptr_sibling->ptr_left)->color == red) {
                isReddestChildrenRight = false;
                ptr_siblings_red_child = static_cast<RbNode*>(ptr_sibling->ptr_left);
            }
        }

        //Case 2
        //Needs rotation
        if (ptr_siblings_red_child != nullptr) {
            if (isSiblingRight) {
                if (isReddestChildrenRight) {
                    RightRightCase(ptr_siblings_red_child);
                }
                else {
                    RightLeftCase(ptr_siblings_red_child);
                    ptr_sibling = ptr_siblings_red_child;
                }
            }
            else {
                if (isReddestChildrenRight) {
                    LeftRightCase(ptr_siblings_red_child);
                    ptr_sibling = ptr_siblings_red_child;
                }
                else {
                    LeftLeftCase(ptr_siblings_red_child);
                }
            }
            ptr_grandparent->color = red;

            if (ptr_sibling->ptr_left != nullptr) {
                static_cast<RbNode*>(ptr_sibling->ptr_left)->color = black;
            }
            if (ptr_sibling->ptr_right != nullptr) {
                static_cast<RbNode*>(ptr_sibling->ptr_right)->color = black;
            }
            ptr_sibling->color = Color::red;
        }
        //Case 3 recoloring
        else {
            recolor(ptr_grandparent, ptr_parent);
        }
    }
    //Case 4 Sibling is red
    else {
        if (isSiblingRight) {
            RightRightCase(ptr_sibling->ptr_right);
        }
        else {
            LeftLeftCase(ptr_sibling->ptr_left);
        }
        ptr_grandparent->color = red;
        ptr_sibling->color = black;
        recolor(ptr_grandparent, ptr_parent);
    }
}




void RedBlackTree::recolor(RbNode* node, RbNode* from /*= nullptr*/) {
    if (from != nullptr) {
        //Paint sibling red
        //They must be black
        if (node->ptr_left == from && node->ptr_right != nullptr) {
            static_cast<RbNode*>(node->ptr_right)->color = Color::red;
        }
        else if (node->ptr_right == from && node->ptr_left != nullptr) {
            static_cast<RbNode*>(node->ptr_left)->color = Color::red;
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

char const* RedBlackTree::GetType() const{ return "RB";}