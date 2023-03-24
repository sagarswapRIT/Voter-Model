#include <iostream>
#include <vector>
#include "../include/Node.hpp"
using namespace std;
//TODO: Change all call by values to call by reference
class Node{
    public:  
    Node(int identity)
    {
        this->id = identity;
        this->state = false;
    }

    bool getState(){
        return this->state;
    }

    void changeState(){
        this->state=!(this->state);
    }

    int getId(){
        return id;
    }

    void addNeighbour(int newneigh){
        for(int i=0; i<this->neighbours.size(); i++){
            if(neighbours[i]==newneigh){
                cout<<"It is already a neighbour"<<endl;
                break;
            }
        }
        neighbours.push_back(newneigh);
        cout<<"New neighbour added"<<endl;
    }


    private:
    bool state;
    int id;
    vector<int> neighbours;
};

int main(){
    cout<<"Hello World"<<endl;
    return 0;
}
