#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
#include "../include/ComplexNetwork.hpp"
#include "../include/Node.hpp"
using namespace std;
//TODO: Change all call by values to call by reference
//TODO: Optimise the search fucntionality in nodeList since they are sorted and can be referenced directlyadsadas

//to compile the code in the terminal: g++ ComplexNetwork.cpp -o ComplexNetwork Shifted to Visual Studio Code
//to run the code in the terminal: ./ComplexNetworkyo


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

//This function randomly creates a network
// void generateRandomNetwork(){
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

Node ComplexNetwork::getNode(int identity){
    if(nodeCount>identity)
        return nodeList[identity];
    cout<<"Node with id = "<<identity<<" not found";
    return NULL;
}

//This function creates a network where all the edges have been input from a text file
void ComplexNetwork::loadData(std::string filename){
    fstream file;
    file.open(filename, ios::in);
    string tp;
    int cc=0;
    while(getline(file, tp)){
        cout<< tp <<"\n";
        std::istringstream is(tp);
        int inputNode, outputNode;
        is>>inputNode;
        is>>outputNode;
        if(cc==0){
            generateNetwork(inputNode, outputNode);
            cc++;
        }
        else{
            Node node=getNode(inputNode);
            node.addNeighbour(outputNode);
        }        
    }
    file.close();
}

void ComplexNetwork::generateNetwork(int nodeC, int edgeC){
    this->nodeCount=nodeC;
    this->edgeCount=edgeC;
    for(int i=0; i<nodeC; i++){
        Node newNode(i);
        this->nodeList.push_back(newNode);
    }

}
     
int nodeCount, edgeCount, cardinality;
std::vector<Node> nodeList;
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
