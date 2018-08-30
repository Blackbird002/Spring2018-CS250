/*
Riad Shash (Ray)
CS 250
Program 4
*/

#include <iostream>
#include <fstream>
#include "Qtype.hpp"
#include "HPQueue.hpp"
using namespace std;

enum colors {white, gray, black};

//maxVert is the # of verticies of graph (needs to be changed for other graphs)
const int maxVert = 13;

//The adjacency matrix
int adjMatrix[maxVert][maxVert];

//outputFile global to avoid constant passing as parameter
ofstream outputFile;

//Used to make the list of edges that makes up MST
int SourceArray[maxVert];
int destinationArray[maxVert];

void printAllEdges(int maxVert);
int convertLetterToIndex(char inputLetter);
char convertIndexToChar(int inIndex);
void initAdjMatrix();
void initColorArray();
void printAdjMatrix();
void readInGraphFromFile(string fileName);
int PrimsMST(char start);

int main()
{
    int totalWeight = 0;
    initAdjMatrix();
    readInGraphFromFile("graph.txt");

    outputFile.open("Result.txt");
    if(outputFile.fail()){
        cout<<"Error creating file! \n";
    }

    printAdjMatrix();

    //Run prim's algorithm starting at Vertex 'A'
    totalWeight = PrimsMST('A');

    printAllEdges(maxVert);
    outputFile<<endl;
    outputFile<<"Total of weights = " <<totalWeight <<endl;

    cout <<"END OF LINE" << endl;
    cin.ignore();
    return 0;
}

//Converts a letter to an index that will be used with the graph
int convertLetterToIndex(char inputLetter){
    return (inputLetter - 'A');
}

//Converts an index used in graph to the appropriate letter
char convertIndexToChar(int inIndex){
    return (char(inIndex + 'A'));
}

//Initializes the Matrix
void initAdjMatrix()
{
    //For every row
    for(int i = 0; i < maxVert; i++)
    {
        //For every col
        for(int j = 0; j < maxVert; j++) adjMatrix[i][j] = 0;
    }
}

//Prints the edges
void printAllEdges(int maxVert){
    char source, dest;
    outputFile<<endl;
    outputFile<<"List of edges that makes up MST: \n";

    //Skipping index 0 since it is not an Edge (We start at A)
    for(int i = 1; i <maxVert; i++){
        source = convertIndexToChar(SourceArray[i]);
        dest = convertIndexToChar(destinationArray[i]);

        outputFile<<source <<" - " <<dest <<endl;
    }   
    cout<<endl;
}

void initColorArray(colors color[]){
    for(int i = 0; i < maxVert; i++){
        color[i] = white;
    }
}

void printAdjMatrix(){
    //Adds letters up top to make it easier to read
    outputFile<<"Adjacency Matrix: \n";
    outputFile<<endl;
    char letter = 'A';
    outputFile<<"  ";
    for(int i = 0; i < maxVert; i++){
        outputFile<<letter; outputFile<<" ";
        letter++;
    }
    outputFile<<endl;
    letter = 'A';

    for(int i = 0; i < maxVert; i++){
        //Also adds letters on the left to make it easier to read
        outputFile<<letter; outputFile<<" ";
        for(int j = 0; j < maxVert; j++)
            outputFile<<adjMatrix[i][j] <<" ";
        letter++;
        outputFile<<endl;
    }
}

void readInGraphFromFile(string fileName)
{
    char chStart, chDest, ch;
    int start, dest;
    int wt;

    ifstream inputFile;
    inputFile.open(fileName);

    if(inputFile.fail()){
        cout<<"Error reading in file! \n";
        return;
    }

    for(int k = 0; k < maxVert; k++)
        for(int i = 0; i < maxVert; i++)
            for(int j = 0; j < maxVert; j++){
                inputFile>>chStart >>ch >>chDest >>ch >>wt;
                start = convertLetterToIndex(chStart);
                dest = convertLetterToIndex(chDest);

                adjMatrix[start][dest] = wt;
                adjMatrix[dest][start] = wt;
            }
    inputFile.close();
}

/*Prim's algorithm
Has access to HPQueue class private members (friend function)*/
int PrimsMST(char start)
{
    //The color matrix
    colors color[maxVert];
    initColorArray(color);
    
    int startIndex, currVert, totalMSTWeight, sourceVert, index;
    Qtype *u;
    startIndex = convertLetterToIndex(start);
    index = 0;
    totalMSTWeight = 0;

    //Declare the HPQueue 
    HPQueue PrimQ = HPQueue();

    //Start phase
    //Start index has no source, so it's set to -1 and wt to 0
    PrimQ.enQ(startIndex,-1, 0);
    color[startIndex] = gray;

    while(!PrimQ.emptyQ())
    {
        u = PrimQ.deQ();
        currVert = u->getVertex();
        sourceVert = u->getSourceVert();
        destinationArray[index] = currVert;
        SourceArray[index] = sourceVert;
        index++;

        //explore each vertex adjacent to u
        for(int i = 0; i < maxVert; i++){
            //If there is an edge with vertex i
            if(adjMatrix[currVert][i] != 0){
                //Check the color of vertex i
                if(color[i] == white){
                    //enQ vertex i
                    PrimQ.enQ(i, currVert, adjMatrix[currVert][i]);

                    //Set vertex i's color to gray
                    color[i] = gray;
                }
                else if (color[i] == gray){
                    //compare vertex i with vertex i on the queue
                    Qtype *prior = PrimQ.Qhead;
                    Qtype *next = PrimQ.Qhead->getlink();
                    while(next != PrimQ.Qtail){
                        if(next->getVertex() == i){
                            //If it has a <= weight, remove it and EnQ new Qtype
                            if(adjMatrix[currVert][i] <= next->getWeight()){
                                //Remove vertex i from queue
                                PrimQ.removeFromQ(next->getVertex());

                                //EnQ the new Qtype vertex i
                                PrimQ.enQ(i,currVert, adjMatrix[currVert][i]);
                            }
                        }
                        prior = next;
                        next = next->getlink();
                    }
                }
                //else if it is black, continue
            }
        }
        color[currVert] = black;
        totalMSTWeight += u->getWeight();
        delete u;
    }
    return totalMSTWeight;
}

