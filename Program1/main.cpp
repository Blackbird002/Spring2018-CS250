/*
Riad Shash (Ray)
CS 250
Program #1 Part B
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int SIZE = 10000;

void swap(double &num1, double &num2);
long int bubbleSort(double array[], const int &arraySize);
long int selectionSort(double array[], const int &arraySize);
long int insertionSort(double array[], const int &arraySize);
void quickSort(int left, int right, double array[], long int &moves);
void printArray(double array[], const int &arraySize, ofstream &output);
bool isSorted(double array[], const int &arraySize);
void readFile(ifstream &input, double array[]);
string printBoolResult(bool &sorted);

int main()
{
    long int moveCount = 0;
    bool isItSorted;

    double *arrayOne, *arrayTwo, *arrayThree, *arrayFour, *arrayFive;
    arrayOne = new double[SIZE];
    arrayTwo = new double[SIZE];
    arrayThree = new double[SIZE+1];
    arrayFour = new double[SIZE];
    arrayFive = new double[SIZE];

    ifstream inputFile;
    ofstream outputFile;

    inputFile.open("RandomNumbers.dat");
    outputFile.open("output.dat");

    if(inputFile.fail())
        cout<<"ERROR reading in file!\n";
    else{
        readFile(inputFile, arrayOne);
    }

    //Copies the contents of arrayOne to other arrays
    for(int i = 0; i < 10000; i++){
        arrayTwo[i] = arrayOne[i];
        arrayThree[i] = arrayOne[i];
        arrayFour[i] = arrayOne[i];
        arrayFive[i] = arrayOne[i];
    }

    outputFile<<"Bubble Sort moves: \n";
    for(int i = 1000; i <= 10000; i += 1000){
        moveCount = bubbleSort(arrayOne,i);
        if(i != 10000){
            for(int j = 0; j < i; j++){
            arrayOne[j] = arrayFive[j];
            }
        }
        outputFile<<moveCount <<" for " <<i <<" elements" <<endl;
    }

    isItSorted = isSorted(arrayOne, 10000);
    outputFile<<"Is arrayOne sorted? " <<printBoolResult(isItSorted) <<endl;
    outputFile<<"------------------------------------------\n";

    outputFile<<endl;
    outputFile<<"Selection Sort moves: \n";
    for(int i = 1000; i <= 10000; i += 1000){
        moveCount = selectionSort(arrayTwo,i);
        if(i != 10000){
            for(int j = 0; j < i; j++){
            arrayTwo[j] = arrayFive[j];
            }
        }
        outputFile<<moveCount <<" for " <<i <<" elements" <<endl;
    }
    isItSorted = isSorted(arrayTwo, 10000);
    outputFile<<"Is arrayTwo sorted? " <<printBoolResult(isItSorted) <<endl;
    outputFile<<"------------------------------------------\n";

    outputFile<<endl;
    outputFile<<"Insertion Sort moves: \n";
    for(int i = 1000; i <= 10000; i += 1000){
        moveCount = insertionSort(arrayThree,i);
        if(i != 10000){
            for(int j = 0; j < i; j++){
            arrayThree[j] = arrayFive[j];
            }
        }
        outputFile<<moveCount <<" for " <<i <<" elements" <<endl;
    }
    isItSorted = isSorted(arrayThree, 10000);
    outputFile<<"Is arrayThree sorted? " <<printBoolResult(isItSorted) <<endl;
    outputFile<<"------------------------------------------\n";
    outputFile<<endl;

    outputFile<<"Quick Sort moves: \n";
    long int quickMoves;
    for(int i = 1000; i <= 10000; i += 1000){
        quickMoves = 0;
        quickSort(0,i-1, arrayFour, quickMoves);
        if(i != 10000){
            for(int j = i; j < i; j++){
            arrayFour[j] = arrayFive[j];
            }
        }
        outputFile<<quickMoves <<" for " <<i <<" elements" <<endl;
    }
    isItSorted = isSorted(arrayFour, 10000);
    outputFile<<"Is arrayFour sorted? " <<printBoolResult(isItSorted) <<endl;

    delete[] arrayOne;
    delete[] arrayTwo;
    delete[] arrayThree;
    delete[] arrayFour;
    delete[] arrayFive;

    outputFile.close();

    cout<<"END OF LINE\n";
    cin.ignore();
    return 0;
}

/*
Bubble sort according to pseudo code given in class
Returns the number of moves to sort arraySize elements
*/
long int bubbleSort(double array[], const int &arraySize)
{
    long int move = 0;
    int i,j;
    for (i = 0; i < arraySize-1; i++){
        for(j = 0; j < arraySize-1; j++){
            if(array[j] > array[j+1]){
                swap(array[j], array[j+1]);
                move += 3;
            }
        }
    }
    return move;
}


//Needs an array +1 bigger than the size
long int insertionSort(double array[], const int &arraySize)
{
    long int move = 0;
    int j,save;
    for(int k = arraySize - 1; k >= 0; k--){
        j = k + 1;
        save = array[k];
        array[arraySize] = save;
        move ++;
        while (save > array[j]){
            array[j-1] = array[j];
            move++;
            j = j + 1;
        }
        array[j-1] = save;
        move++;
    }
    return move;
}

long int selectionSort(double array[], const int &arraySize)
{
    long int move = 0;
    int k,j,small;
    if (arraySize > 0)
    {
        for(k = 0; k< arraySize-1; k++){
            small = k;
            for(j = k+1; j < arraySize; j++){
                if(array[j] < array[small])
                    small = j;
            }
            if (k != small){
                swap(array[k],array[small]);
                move += 3;
            }
        }
    }
    return move;
}


//The moves input parameter is incremented when a move is done
void quickSort(int left, int right, double array[], long int &moves)
{
    int j,k;
    if (left < right){
        j = left;
        k = right + 1;
        do{
            do{
                j = j + 1;
            } while((array[j] < array[left]) && (j <= k));

            do{
                k = k - 1;
            } while((array[k] > array[left]) && (k >= 0));

            if (j < k){
                swap(array[j], array[k]);
                moves += 3;
            }
        } while(j <= k);

        swap(array[left], array[k]);
        moves +=3;
        quickSort(left, k-1, array, moves);
        quickSort(k+1, right, array, moves);
    }
}

//Prints array to file if called
void printArray(double array[], const int &arraySize, ofstream &output)
{
    for(int i = 0; i < arraySize; i++){
        output<<array[i] <<endl;
    }
}

//Checks if array is sorted
bool isSorted(double array[], const int &arraySize)
{
    bool sorted = true;
    for (int i = 0; i < arraySize - 1; i++){
        if(array[i] > array[i+1])
            sorted = false;
    }
    return sorted;
}

//Swaps two given array elements
void swap(double &num1, double &num2)
{
    double temp = num1;
    num1 = num2;
    num2 = temp;
}

//Reads in numbers from file to array
void readFile(ifstream &input, double array[])
{
    string line;
    string newline;
    double number;
    int i = 0;

    for(int j = 0; j < 10000; j++){
        i = 0;
        line = "";
        newline = "";
        getline(input,line);

        //Gets rid of all the whitespace in the string
        while(line[i] != '\0'){
            if(line[i] != ' ')
                newline = newline + line[i];
            i++;
        }

        //Converts the string to a double type
        number = stod(newline);
        array[j] = number;
    }
    input.close();
}

//Helper function for boolean results
string printBoolResult(bool &sorted)
{
    string result = "NO!";
    if (sorted == true)
        result = "Yes!";
    return result;
}
