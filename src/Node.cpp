#include <iostream>
#include <vector>
#include "../include/Node.hpp"
using namespace std;
//TODO: Change all call by values to call by reference
    
Node::Node(int identity)
{
    this->id = identity;
    this->state = false;
}

bool Node::getState(){
    return this->state;
}

void Node::changeState(){
    this->state=!(this->state);
}

int Node::getId(){
    return id;
}

void Node::addNeighbour(int newneigh){
    if(!isNeighbour(newneigh)){
        neighbours.push_back(newneigh);
        cout<<"New neighbour added"<<endl;
    }
    else
        cout<<"Cannot add neighbour "<<newneigh<<"to the node "<<this->getId()<<endl;
}

bool Node::isNeighbour(int identity){
    for(int i=0; i<this->neighbours.size(); i++)
        if(neighbours[i]==identity)
            return true;
    return false;
}

bool state;
int id;
vector<int> neighbours;

int main(){
    cout<<"Hello World"<<endl;
    return 0;
}
