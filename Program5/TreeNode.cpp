#include "TreeNode.hpp"

TreeNode::TreeNode(){
    id = -1;
    left = nullptr;
    right = nullptr;
    threaded = false;
}

TreeNode::TreeNode(int newId){
    id = newId;
    left = nullptr;
    right = nullptr;
    threaded = false;
}

TreeNode::TreeNode(int newId, TreeNode *newLeft, TreeNode *newRight){
    id = newId;
    left = newLeft;
    right = newRight;
    threaded = false;
}

int TreeNode::getId() const{
    return id;
}

TreeNode* TreeNode::getLeft() const{
    return left;
}

TreeNode* TreeNode::getRight() const{
    return right;
}

bool TreeNode::isThreaded() const{
    return threaded;
}

void TreeNode::setThreaded(bool newBool){
    threaded = newBool;
}

void TreeNode::setLeft(TreeNode *newLeft){
    left = newLeft;
}

void TreeNode::setRight(TreeNode *newRight){
    right = newRight;
}

void TreeNode::setId(int newId){
    id = newId;
}

bool TreeNode::operator==(const TreeNode& obj1) const{
    return (id == obj1.id);
}

bool TreeNode::operator!=(const TreeNode& obj1) const{
    return (id != obj1.id);
}

bool TreeNode::operator>(const TreeNode& obj1) const{
    return (id > obj1.id);
}

bool TreeNode::operator<(const TreeNode& obj1) const{
    return (id < obj1.id);
}
