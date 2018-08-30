/*
Riad Shash (Ray)
CS 250
Program 5
*/

#ifndef THREADEDBST_HPP_INCLUDED
#define THREADEDBST_HPP_INCLUDED

#include "TreeNode.hpp"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

class ThreadedBST
{
public:
    //Constructors (functions like createTree)
    ThreadedBST();
    ThreadedBST(int rootId);

    //Destructor (uses the iterative in-order algorithm)
    ~ThreadedBST();

    TreeNode* getRoot() const;
    void insert(int insertId);

    //Recursive in-order traversal
    void rInorder(TreeNode* c, std::ofstream& outputFile) const;

    //Iterative in-order tree traversal
    void iterativeInorder(std::ofstream& outputFile) const;

private:
    bool emptyTree() const;
    void searchTree(TreeNode* &newNode, TreeNode* &parent);
    TreeNode *root;

};

#endif // THREADEDBST_HPP_INCLUDED
