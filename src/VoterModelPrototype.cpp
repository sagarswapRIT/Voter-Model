#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Node{
    public:
    Node(int identity){
        this->id = identity;
        this->state = false;
    }

    bool getState(){
        return this->state;
    }

    void changeState(){
        this->state = !this->getState();
    }

    int getId(){
        return this->id;
    }

    void addNeighbour(int newneigh){
        if(!isNeighbour(newneigh)){
            neighbours.push_back(newneigh);
            //cout<<"New neighbour added, size = "<<neighbours.size()<<endl;
        }
        else
            cout<<"Cannot add neighbour "<<newneigh<<"to the node "<<this->getId()<<endl;
    }

    void printAllNeighbours(int lim){
        for(int i=0; i<this->neighbours.size() && i<lim; i++)
            cout<<this->neighbours[i]<<", ";
        cout<<endl;
    }

    int id;
    bool state;
    vector<int> neighbours;

    bool isNeighbour(int identity){
        for(int i=0; i<this->neighbours.size(); i++)
            if(neighbours[i]==identity)
                return true;
        return false;
    }
};

class ComplexNetwork{
    public:
    ComplexNetwork(std::string fname){
        this->filename=fname;
    }

    void loadData(){
        fstream file;
        file.open(filename, ios::in);
        string tp;
        int cc=0;
        while(getline(file, tp)){
            //cout<< tp <<"\n";
            std::istringstream is(tp);
            int inputNode, outputNode;
            is>>inputNode;
            is>>outputNode;
            if(cc==0){
                generateNetwork(inputNode, outputNode);
                cc++;
            }
            else{
                Node* node=getNode(inputNode);
                //Node node=&nodePtr;
                node->addNeighbour(outputNode);
            }        
        }
        file.close();
    }

    Node* getNode(int identity){
        if(nodeCount>identity)
            return nodeList[identity];
        cout<<"Node with id = "<<identity<<" not found";
        return NULL;
    }

    void printAllEdges(int lim){
        for(int i=0; i<nodeList.size(); i++){
            Node node=*nodeList[i];
            cout<<node.getId()<<" -> ";
            node.printAllNeighbours(lim);
        }
    }

    private:
    int nodeCount, edgeCount;
    std::vector<Node*> nodeList;
    std::string filename;

    void generateNetwork(int nodeC, int edgeC){
        this->nodeCount=nodeC;
        this->edgeCount=edgeC;
        for(int i=0; i<nodeC; i++){
            Node* newNode=new Node(i);;
            this->nodeList.push_back(newNode);
            //cout<<"Generate nw"<<&newNode<<endl;
        }
    }
};

int main(){
    cout<<"Hello World"<<endl;
    ComplexNetwork network("../data/facebook_combined.txt");
    network.loadData();
    network.printAllEdges(10);
}