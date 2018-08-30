/*
Riad Shash (Ray)
CS 250
Program 5
*/

#include <iostream>
#include <fstream>
#include "TreeNode.hpp"
#include "ThreadedBST.hpp"

using namespace std;

//Max number of elements in tree array
const int MAXTREE = 100;
const int INITVAL = -1;

//The index of root (array BST)
const int ROOTINDEX = 1;

//Output file global to avoid constant passing as parameter
ofstream outputFile;

//BST array functions
void createTree(int Tree[]);
bool emptyTree(int Tree[]);
bool fullTree(int Tree[]);
void insertTree(int Tree[], int newInput);
void TreeInOrderRec(int Tree[], int i);

int main()
{
    cout<<endl;

    //Create the TBST
    ThreadedBST TBST = ThreadedBST();

    //Declare the Tree array
    int ArrTree[MAXTREE];
    createTree(ArrTree);

    //Read in and insert all the values from the file
    ifstream inputFile;
    inputFile.open("Input.txt");

    if(inputFile.fail())
        cout<<"Error reading Input.txt file! \n";
    else{
        int number;
        while(!inputFile.eof()){

            inputFile>>number;

            //Insert into the Threaded BST
            TBST.insert(number);

            //Insert into the array tree
            insertTree(ArrTree, number);
        }
    }

    outputFile.open("Output.txt");

    if(outputFile.fail()){
        cout<<"Error creating Output.txt \n";
    }
    else{
        outputFile<<endl;

        //This is the recursive in-order print
        outputFile<<"Recursive in-order TBST traversal: \n";
        TBST.rInorder(TBST.getRoot(), outputFile); outputFile<<endl;
        outputFile<<endl;

        //This is the iterative in-order print
        outputFile<<"Iterative in-order TBST traversal: \n";
        TBST.iterativeInorder(outputFile); outputFile<<endl;
        outputFile<<endl;

        //This is the recursive Tree Array in-order print
        outputFile<<"Recursive in-order Array BST traversal: \n";
        TreeInOrderRec(ArrTree, ROOTINDEX);
    }

    cout<<"END OF LINE \n";
    cin.ignore();
    return 0;
}

void createTree(int Tree[]){
    for(int i = 0; i < MAXTREE; i++) Tree[i] = INITVAL;
}

bool emptyTree(int Tree[]){
    //ArrTree[1] is the root of the tree
    return (Tree[ROOTINDEX] == INITVAL);
}

bool fullTree(int Tree[]){
    return (Tree[MAXTREE - 1] != INITVAL);
}

void insertTree(int Tree[], int newInput){
    int i;
    if(!emptyTree(Tree)){
        i = ROOTINDEX;
        while(Tree[i] != INITVAL && i < MAXTREE){
            if(newInput < Tree[i])
                i = 2*i;
            else
                i = 2*i + 1;
        }
        if(i < MAXTREE)
            Tree[i] = newInput;
        else
            cout<<"Tree is full! \n";
    }
    else
        Tree[ROOTINDEX] = newInput;
}

//Tree Array Recursive in-order traversal
void TreeInOrderRec(int Tree[], int i){
    if(Tree[2*i] != INITVAL) TreeInOrderRec(Tree, 2*i);
    outputFile<<Tree[i] <<" ";
    if(Tree[2*i + 1] != INITVAL) TreeInOrderRec(Tree, 2*i + 1);
}
