#include "ThreadedBST.hpp"

ThreadedBST::ThreadedBST(){
    root = new TreeNode(-1,nullptr,nullptr);
}

ThreadedBST::ThreadedBST(int rootId){
    root = new TreeNode(rootId,nullptr,nullptr);
}

/*Destructor
This tree is threaded, so a typical destructor for a regular
BST does not work. I used the iterative traversal algorithm
showed in class with a slight modification. I keep track of
the previously visited node and then delete it as c gets
assigned to the next node. Then root is deleted
*/
ThreadedBST::~ThreadedBST(){
    //Start at the root
    TreeNode* c = root;

    //The node that will be deleted when c moves on
    TreeNode* prev;
    while(c != nullptr){
        while(c->getLeft() != nullptr) c = c->getLeft();
        while(c->isThreaded()){
            prev = c;
            c = c->getRight();
            delete prev;
        }
        prev = c;
        c = c->getRight();
        delete prev;
    }
    //Delete the root
    delete root;
}

TreeNode* ThreadedBST::getRoot() const{
    return root;
}

bool ThreadedBST::emptyTree() const{
    return (root->getId() == -1);
}

//Iterative in-order traversal of the TBST
void ThreadedBST::iterativeInorder(std::ofstream& outputFile) const{
    //We start at the root
    TreeNode* c = root;
    while(c != nullptr){
        while(c->getLeft() != nullptr) c = c->getLeft();
        outputFile<<c->getId() <<" ";
        while(c->isThreaded()){
            c = c->getRight();
            outputFile<<c->getId() <<" ";
        }
        c = c->getRight();
    }
}

//Recursive in-order traversal of the TBST
void ThreadedBST::rInorder(TreeNode *c, std::ofstream& outputFile) const{
    if(c->getLeft() != nullptr) rInorder(c->getLeft(), outputFile);
    outputFile<<c->getId() <<" ";
    if(c->getRight() != nullptr && !c->isThreaded()) rInorder(c->getRight(), outputFile);
}

//Finds the parent of Knew
void ThreadedBST::searchTree(TreeNode* &newNode, TreeNode* &parent){
    parent = nullptr;
    TreeNode* c = root;

    while(c != nullptr){
        parent = c;
        if(*newNode < *c)
            c = c->getLeft();
        else if (!c->isThreaded())
            c = c->getRight();
        else
            c = nullptr;
    }
}

void ThreadedBST::insert(int insertId){
    TreeNode *knew, *parent;
    if(!emptyTree()){
        //Constructor sets id to -1 and left + right to nullptr
        knew = new TreeNode(insertId);

        //Searches for the parent of knew
        searchTree(knew, parent);

        if(*knew < *parent){
            //knew will be a left child
            knew->setThreaded(true);
            knew->setRight(parent);
            parent->setLeft(knew);
        }
        else{
        //knew will be a right child
            //Is the child threaded or not?
            if(parent->isThreaded() == true){
                knew->setThreaded(true);
                knew->setRight(parent->getRight());
                parent->setRight(knew);
                parent->setThreaded(false);
            }
            else{
                knew->setRight(parent->getRight());
                knew->setThreaded(parent->isThreaded());
                parent->setRight(knew);
                parent->setThreaded(false);
            }
        }
    }
    else{
        //Value is set in root
        root->setId(insertId);
    }
}