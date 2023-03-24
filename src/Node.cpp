#include <iostream>
#include <vector>
#include <algorithm>
#include "../include/Node.hpp"
using namespace std;

class Node{

    int state, id;

    public:
    Node* neighbours;
  
    // Default constructor
    Node()
    {
        data = 0;
        next = NULL;
    }
  
    // Parameterised Constructor
    Node(int identity)
    {
        this->id = identity;
        this->next = NULL;
        this->state = 0;
    }
};

int main(){
    cout<<"Hello World"<<endl;
    Node n1(1);
    Node n2(2);
    n2.connectNodes(n1, n2);
    vector<Node> vec=n2.getNeighbours();
    
    n2.connectNodes(n1, n2);
    n1.addNeighbour(n2);
}
