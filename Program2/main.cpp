/*
Riad Shash (Ray)
CS 250
Program #2 - Sets ADT
*/

#include <iostream>
#include <fstream>

using namespace std;

//Made the outputFile global to avoid constant passing into functions
ofstream outputFile;
const int maxNum = 'Z' + 1;

void printBoolResult(bool result);
void init(bool universal[], bool vowel[], bool myname[]);
void printSet(bool set[]);
void getSetFromFile(bool myName[]);
void makeEmptySet(bool set[]);
bool areSetsEqual(bool set1[], bool set2[]);
void unionSets(bool set1[], bool set2[], bool result[]);
void intersectionOfSets(bool set1[], bool set2[], bool result[]);
void differenceOfSets(bool set1[], bool set2[], bool result[]);
bool isSubset(bool set1[], bool set2[]);


int main()
{
    outputFile.open("TestResults.txt");
    outputFile<<"*****************************************************************\n";
    outputFile<<"For parts #1 & #2, please look at source code. \n";

    //Part #1
    bool UNIVERSAL[maxNum];
    bool VOWEL[maxNum];
    bool MYNAME[maxNum];

    //Part#2 - Initialization of the sets
    init(UNIVERSAL,VOWEL,MYNAME);

    outputFile<<"*****************************************************************\n";
    outputFile<<"Part #3 - Testing printSet() function: \n";
    outputFile<<endl;

    outputFile<<"Printing the UNIVERSAL Set: \n";
    printSet(UNIVERSAL);

    outputFile<<"Printing the VOWEL Set: \n";
    printSet(VOWEL);

    outputFile<<"Printing the MYNAME Set: \n";
    printSet(MYNAME);

    outputFile<<"*****************************************************************\n";
    outputFile<<"Part #4 - Testing the unionSets() function: \n";
    outputFile<<endl;

    bool resultSet[maxNum];

    makeEmptySet(resultSet);
    outputFile<<"VOWEL union MYNAME is: \n";
    unionSets(VOWEL, MYNAME, resultSet);
    printSet(resultSet);

    outputFile<<"*****************************************************************\n";
    outputFile<<"Part #5- Testing the intersectionOfSets() function: \n";
    outputFile<<endl;

    makeEmptySet(resultSet);
    outputFile<<"MYNAME intersection VOWEL is: \n";
    intersectionOfSets(MYNAME, VOWEL, resultSet);
    printSet(resultSet);

    outputFile<<"*****************************************************************\n";
    outputFile<<"Part #6- Testing the differenceOfSets() function: \n";
    outputFile<<endl;

    makeEmptySet(resultSet);
    outputFile<<"Difference of MYNAME and VOWEL is: \n";
    differenceOfSets(MYNAME, VOWEL, resultSet);
    printSet(resultSet);

    outputFile<<"*****************************************************************\n";
    outputFile<<"Part #7 - Testing the areSetsEqual() function: \n";
    outputFile<<endl;

    outputFile<<"Is VOWEL equal to MYNAME? \n";
    printBoolResult(areSetsEqual(VOWEL, MYNAME));
    outputFile<<endl;

    outputFile<<"Is MYNAME equal to MYNAME? \n";
    printBoolResult(areSetsEqual(MYNAME, MYNAME));
    outputFile<<endl;

    outputFile<<"*****************************************************************\n";
    outputFile<<"Part #8 (Extra Credit) - Testing the isSubset() function: \n";
    outputFile<<endl;

    //Created sets of my own to further test subsets
    bool set1[maxNum];
    bool set2[maxNum];
    makeEmptySet(set1);
    makeEmptySet(set2);

    for(int i = 'A'; i <= 'G'; i++) set1[i] = true;
    set1['Z'] = true;
    outputFile<<"Set1 is: \n";
    printSet(set1);

    for(int i = 'A'; i <= 'L'; i++) set2[i] = true;
    set2['Z'] = true;
    outputFile<<"Set2 is: \n";
    printSet(set2);

    outputFile<<"Is set1 a subset of set2? \n";
    printBoolResult(isSubset(set1,set2));
    outputFile<<endl;

    outputFile<<"Is set2 a subset of set1? \n";
    printBoolResult(isSubset(set2,set1));
    outputFile<<endl;

    outputFile<<"Is MYNAME a subset of UNIVERSAL? \n";
    printBoolResult(isSubset(MYNAME,UNIVERSAL));
    outputFile<<endl;

    outputFile<<"*****************************************************************\n";
    outputFile.close();

    cout<<"Please see the file: TestResults.txt in the current directory.\n";
    cout<<"END OF LINE \n";

    cin.ignore();
    return 0;
}

void init(bool universal[], bool vowel[], bool myname[])
{
    //Sets up the universal set
    for(int i = 'A'; i <= 'Z'; i++)
        universal[i] = true;

    //Sets up the vowel set
    for(int i = 'A'; i <= 'Z'; i++)
    {
        if (i == 'A' || i == 'E' || i == 'I' || i == 'O'|| i == 'U')
            vowel[i] = true;
        else
            vowel[i] = false;
    }

    //Sets up the myname set...
    makeEmptySet(myname);
    getSetFromFile(myname);
}

//Builds a set from a file
void getSetFromFile(bool myname[])
{
    ifstream inputFile;
    string line;
    char letter;

    inputFile.open("MyName.dat");
    if(inputFile.fail()){
        cout<<"ERROR reading in file!\n";
        return;
    }

    //Goes through file and modifies the myname set with the letters that exist
    while (!inputFile.eof())
    {
        getline(inputFile, line);
        letter = line[0];

        //avoids a compiler warning with the int-type cast
        myname[int(letter)] = true;
    }

    inputFile.close();
}

//Prints the set to the file
void printSet(bool set[])
{
    for(int i = 'A'; i <= 'Z'; i++)
    {
        if (set[i])
            outputFile<<char(i) <<" ";
        else
            outputFile<<"_ ";
    }
    outputFile<<endl;
    outputFile<<endl;
}

//Makes the set an empty set
void makeEmptySet(bool set[])
{
    for(int i = 'A'; i <= 'Z'; i++) set[i] = false;
}

bool areSetsEqual(bool set1[], bool set2[])
{
    bool result = true;
    for(int i = 'A'; i <= 'Z'; i++)
    {
        if(set1[i] != set2[i])
            result = false;
    }
    return result;
}

//The union of set1 and set2 = result
void unionSets(bool set1[], bool set2[], bool result[])
{
    for(int i = 'A'; i <= 'Z'; i++)
    {
        if(set1[i] || set2[i])
            result[i] = true;
        else
            result[i] = false;
    }
}

//The intersection of set1 and set2 = result
void intersectionOfSets(bool set1[], bool set2[], bool result[])
{
    for(int i = 'A'; i <= 'Z'; i++)
    {
        if(set1[i] && set2[i])
            result[i] = true;
        else
            result[i] = false;
    }
}

//The difference of set1 and set2 = result
void differenceOfSets(bool set1[], bool set2[], bool result[])
{
    for(int i = 'A'; i <= 'Z'; i++)
    {
        if(set1[i] && !set2[i])
            result[i] = true;
        else
            result[i] = false;
    }
}

//Is set1 a subset of set2?
bool isSubset(bool set1[], bool set2[])
{
    bool result = true;
    for(int i = 'A'; i <= 'Z'; i++)
    {
        if(set1[i])
            if(!set2[i])
                result = false;
    }
    return result;
}

//Prints the result of bools (helper function)
void printBoolResult(bool result)
{
    if(result)
        outputFile<<"Yes! \n";
    else
        outputFile<<"No! \n";
}
