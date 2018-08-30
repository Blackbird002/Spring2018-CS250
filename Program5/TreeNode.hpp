/*
Riad Shash (Ray)
CS 250
Program 5

    I made TreeNode into a class. Overloading the operators
    allows the direct comparison of the TreeNodes.
*/

#ifndef TREENODE_HPP_INCLUDED
#define TREENODE_HPP_INCLUDED

class TreeNode
{
public:
    //Constructors
    TreeNode();
    TreeNode(int newId);
    TreeNode(int newId, TreeNode *newLeft, TreeNode *newRight);

    //Accessors
    TreeNode* getLeft() const;
    TreeNode* getRight() const;
    int getId() const;
    bool isThreaded() const;

    //Mutators
    void setLeft(TreeNode *newLeft);
    void setRight(TreeNode *newRight);
    void setId(int newId);
    void setThreaded(bool newBool);

    //Overloaded operators
    bool operator ==(const TreeNode& obj1) const;
    bool operator !=(const TreeNode& obj1) const;
    bool operator >(const TreeNode& obj1) const;
    bool operator <(const TreeNode& obj1) const;

private:
    int id;
    bool threaded;
    TreeNode *left;
    TreeNode *right;

};

#endif // TREENODE_HPP_INCLUDED
