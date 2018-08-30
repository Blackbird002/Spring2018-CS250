/*
Riad Shash (Ray)
CS 250
Program 4
    I decided to create a class for Qtype (the nodes in the HPQueue)
    to make the code easier to read and so I could overload the >= operator.
    This allows me to directly compare the Qtype nodes in the HPQueue.
*/

#ifndef QTYPE_HPP_INCLUDED
#define QTYPE_HPP_INCLUDED

class Qtype
{
public:
    //Constructors
    Qtype();
    Qtype(int inputVertex, int inSourceVertex, int inputWeight, Qtype* l);

    //Accessors
    int getVertex();
    int getWeight();
    int getSourceVert();
    Qtype* getlink();

    //Mutators
    void setLink(Qtype* newLink);

    //Overloaded Operators
    bool operator ==(const Qtype& obj1) const;
    bool operator >(const Qtype& obj1) const;
    bool operator <(const Qtype& obj1) const;
    bool operator >=(const Qtype& obj1) const;

private:
    int vertex, weight, sourceVertex;
    Qtype *link;
};

#endif // QTYPE_HPP_INCLUDED