#include "Qtype.hpp"

Qtype::Qtype(){
    vertex = -1;
    sourceVertex = -1;
    weight = 0;
    link = nullptr;
}

Qtype::Qtype(int inputVertex,int inSourceVertex, int inputWeight, Qtype* l){
    vertex = inputVertex;
    sourceVertex = inSourceVertex;
    weight = inputWeight;
    link = l;
}

void Qtype::setLink(Qtype* newLink){
    link = newLink;
}

int Qtype::getVertex(){
    return vertex;
}

int Qtype::getWeight(){
    return weight;
}

int Qtype::getSourceVert(){
    return sourceVertex;
}

Qtype* Qtype::getlink(){
    return link;
}

bool Qtype::operator==(const Qtype& obj1) const{
    return(weight == obj1.weight);
}

bool Qtype::operator>(const Qtype& obj1) const{
    return(weight > obj1.weight);
}

bool Qtype::operator<(const Qtype& obj1) const{
    return(weight < obj1.weight);
}

bool Qtype::operator>=(const Qtype& obj1) const{
    return(weight >= obj1.weight);
}
