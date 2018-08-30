#include <iostream>
#include "HPQueue.hpp"

using std::cout;
using std::endl;

//Constructor
HPQueue::HPQueue(){
    Qhead = new Qtype(-1,-1,0,nullptr);
    Qtail = new Qtype(99999,99999,99999,nullptr);

    Qhead->setLink(Qtail);
}

/*Destructor
This destructor is sufficient since we use Prim's algorithm which
deQs everything. This is not appropriate for a standard queue.
*/
HPQueue::~HPQueue(){
    delete Qhead;
    delete Qtail;
}

//emptyQ
bool HPQueue::emptyQ() const{
    bool result = false;
    if(Qhead->getlink() == Qtail)
        result = true;

    return result;
}

//enQ
void HPQueue::enQ(int inVertex, int inSource, int inWeight){
    Qtype *prior, *next, *knew;

    //Creates the new Qtype without the link set
    knew = new Qtype(inVertex, inSource, inWeight, nullptr);

    //Set prior and next
    prior = Qhead;
    next = Qhead->getlink();

    while(next != Qtail && *knew >= *next){
        prior = next;
        next = next->getlink();
    }

    //Set the links
    prior->setLink(knew);
    knew->setLink(next);
}

//deQ
Qtype* HPQueue::deQ(){
   Qtype *prior, *next, *removed;

    if (emptyQ())
        std::cout<<"Queue is empty! Operation aborted.";
    else{
        prior = Qhead;
        next = Qhead->getlink();

        //removed points to the Qtype we are going to remove
        removed = next;

        //Re-link Qtypes
        prior->setLink(next->getlink());

        //return the Qtype
        return removed;
    }
}

//removeFromQ
void HPQueue::removeFromQ(int inVertex){
    bool found = false;
    Qtype *prior = Qhead;
    Qtype *next = Qhead->getlink();
    while(next != Qtail && found == false)
    {
        if(next->getVertex()== inVertex)
        {
            //remove Qtype from Q and relink
            prior->setLink(next->getlink());
            delete next;
            found = true;
        }
        prior = next;
        next = next->getlink();
    }
}

//printQ
void HPQueue::printQ() const{
    cout<<endl;
    Qtype *prior, *current;

    //Set prior and next
    prior = Qhead;
    current = Qhead->getlink();

    while(current != Qtail){
        prior = current;
        current = current->getlink();
    }
}
