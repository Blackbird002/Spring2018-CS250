/*
Riad Shash (Ray)
CS 250
Program 4
    I decided to create a class for the HPFIFO queue as well.
    I made PrimeMST a friend function in main to give it access
    to the private members here.
*/

#ifndef HPQUEUE_HPP_INCLUDED
#define HPQUEUE_HPP_INCLUDED
#include "Qtype.hpp"


class HPQueue
{
public:
    //Constructor (functions like createQ)
    HPQueue();

    //Destructor
    ~HPQueue();

    bool emptyQ() const;
    void enQ(int inVertex, int inSource, int inWeight);
    Qtype* deQ();
    void printQ() const;
    void removeFromQ(int vertex);

    //Gives PrimsMST function access to HPQueue's private members in main
    friend int PrimsMST(char start);

private:
    Qtype* Qhead;
    Qtype* Qtail;
};

#endif // HPQUEUE_HPP_INCLUDED
