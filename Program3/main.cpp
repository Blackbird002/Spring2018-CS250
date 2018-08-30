/*
Riad Shash (Ray)
CS 250
Program #3 - HPFIFO queue structure testing program
*/

#include <iostream>
#include <fstream>
using namespace std;

//Made the outputFile global to avoid constant passing into functions
ofstream outputFile;

struct Qtype
{
    int priority;
    string jobname;
    Qtype *link;

    Qtype(){
        priority = 0;
        jobname = "";
        link = nullptr;
    }

    Qtype(int p, string j, Qtype* l){
        priority = p;
        jobname = j;
        link = l;
    }
};

void createQ(Qtype *Qhead, Qtype *Qtail);
void enQ(Qtype *Qhead, Qtype *Qtail, int inputP, string inputJobN);
void deQ(Qtype *Qhead, Qtype *Qtail);
void printQ(Qtype *Qhead, Qtype *Qtail);
bool emptyQ(Qtype *Qhead, Qtype *Qtail);

int main()
{  
    outputFile.open("Output.txt");
    if(outputFile.fail())
        cout<<"Error opening Output.txt! \n";

    Qtype *Qhead, *Qtail;

    //Head
    Qhead = new Qtype(-1,"-1",nullptr);

    //Tail
    Qtail = new Qtype(99999, "99999", nullptr);

    //Creates the Queue
    createQ(Qhead, Qtail);
    enQ(Qhead, Qtail, 5, "Smith123");
    enQ(Qhead, Qtail, 5, "Harold222");
    deQ(Qhead, Qtail);
    enQ(Qhead, Qtail, 2, "Manzanares111");
    enQ(Qhead, Qtail, 1, "Payne051");
    enQ(Qhead, Qtail, 3, "Findlay303");
    deQ(Qhead, Qtail);
    enQ(Qhead, Qtail, 5, "Smith123");
    enQ(Qhead, Qtail, 3, "Fox858");

    outputFile<<endl;

    //Loops through and deQs the rest...
    outputFile<<"Loops through and deQs the rest: \n";
    outputFile<<endl;

    while(!emptyQ(Qhead, Qtail))
        deQ(Qhead, Qtail);

    //Heap cleanup
    delete Qhead;
    delete Qtail;

    cout<<"Please see Output.txt in the current directory. \n";
    cout<<"END OF LINE";
    cin.ignore();
    return 0;
}

void createQ(Qtype *Qhead, Qtype *Qtail){
    //Head link set to tail
    Qhead->link = Qtail;

}

void enQ(Qtype *Qhead, Qtype *Qtail, int inputP, string inputJobN){
    Qtype *prior, *next, *knew;

    //Creates the new Qtype without the link set
    knew = new Qtype(inputP, inputJobN, nullptr);

    //Set prior and next
    prior = Qhead;
    next = Qhead -> link;

    while(next != Qtail && knew->priority >= next->priority)
    {
        prior = next;
        next = next->link;
    }

    //Set the links
    prior->link = knew;
    knew->link = next;
}

void deQ(Qtype *Qhead, Qtype *Qtail){
    Qtype *prior, *next, *removed;

    if (emptyQ(Qhead, Qtail))
        cout<<"Queue is empty! Operation aborted.";
    else{
        prior = Qhead;
        next = Qhead->link;

        //removed points to the Qtype we are going to remove
        removed = next;

        //Re-link Qtypes
        prior->link = next->link;

        //Print the print job that is going to be removed
        outputFile<<"Priority: " <<removed->priority <<"\t Job: " <<removed->jobname  <<endl;

        //delete the Qtype
        delete removed;
    }
}

bool emptyQ(Qtype *Qhead, Qtype *Qtail){
    bool result = false;
    if(Qhead->link == Qtail)
        result = true;

    return result;
}

//Prints the contents of the queue 
void printQ(Qtype *Qhead, Qtype *Qtail){
    Qtype *prior, *current;

    //Set prior and next
    prior = Qhead;
    current = Qhead -> link;

    while(current != Qtail){
        prior = current;
        outputFile<<"Priority: " <<current->priority <<"\t Job: " <<current->jobname  <<endl;
        current = current->link;
    }
}