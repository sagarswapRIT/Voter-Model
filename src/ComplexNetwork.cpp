#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <string>
#include "../include/ComplexNetwork.hpp"
//#include "../include/Node.hpp"
using namespace std;
//TODO: Change all call by values to call by reference
//TODO: Optimise the search fucntionality in nodeList since they are sorted and can be referenced directly

    ComplexNetwork::ComplexNetwork(int nodeC, int edgeC, int card){
        this->nodeCount=nodeC;
        this->edgeCount=edgeC;
        this->cardinality=card;
    }

    int main(){
        ComplexNetwork network(10, 10, 2);
        network.loadData("../data/facebook_combined.txt");
        cout<<"Done"<<endl;
        return 0;
    }

// void generateNetwork(){
//     for(int i=0; i<nodeCount; i++){
//         Node n(i);
//         nodeList.push_back(n);
//     }
// //TODO: Add normal distribution for cardinality
//     for(int i=0; i<nodeCount; i++){
//         int rando=rand()%10;
//         int neighbourCount=cardinality;
//         if(rando<5)
//             neighbourCount+=rand()%3;
//         else
//             neighbourCount-=rand()%3;
//     }
// //TODO: Add code to add neighbours

// }

// Node getNode(int identity){
//     for(int i=0; i<nodeCount; i++){
//         if(nodeList[i].getId()==identity)
//             return nodeList[i];
//     }
//     cout<<"Node with id = "<<identity<<" not found";
//     return NULL;
// }

void ComplexNetwork::loadData(std::string filename){
    fstream file;
    file.open(filename, ios::in);
    string tp;
    while(getline(file, tp)){
        cout<< tp <<"\n";
    }
    file.close();
}

     
int nodeCount, edgeCount, cardinality;
// std::vector<Node> nodeList;
// void connectNodes(int id1, int id2){
//     Node* n1;
//     Node* n2;
//     if(id1==id2){
//         cout<<"Cannot connect a node to itself"<<endl;
//         return;
//     }

//     for(int i=0; i<nodeCount; i++){
//         bool chk1=false, chk2=false;
//         if(nodeList[i].getId()==id1){
//             n1=&nodeList[i];
//             chk1=true;
//         }
//         if(nodeList[i].getId()==id2){
//             n2=&nodeList[i];
//             chk2=true;
//         }
//         if(chk1 && chk2)
//             break;
//     }
//     n1->addNeighbour(id2);
//     n2->addNeighbour(id1);
//     cout<<"Connection between "<<id1<<" and "<<id2<<" established"<<endl;
// }
