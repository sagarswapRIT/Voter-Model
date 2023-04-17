#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Node{
    public:
    Node(int identity, bool status){
        this->id = identity;
        this->state = status;
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
        if(isNeighbour(newneigh)==-1)
            neighbours.push_back(newneigh);
        else
            cout<<"Cannot add neighbour "<<newneigh<<"to the node "<<this->getId()<<endl;
    }

    void deleteNeighbour(int tar){
        vector<int> tempvec;
        for(int i=this->neighbours.size()-1; i>=0; i--){
            int rem=this->neighbours.back();
            this->neighbours.pop_back();
            if(rem==tar)
                break;
            tempvec.push_back(rem);
        }
        for(int i=0; i<tempvec.size(); i++){
            this->neighbours.push_back(tempvec.back());
            tempvec.pop_back();
        }
    }

    void printAllNeighbours(int lim){
        for(int i=0; i<this->neighbours.size() && i<lim; i++)
            cout<<this->neighbours[i]<<", ";
        cout<<endl;
    }

    int id;
    bool state;
    vector<int> neighbours;

    //returns -1 if identity is not a neighbour, else returns index number 
    int isNeighbour(int identity){
        for(int i=0; i<this->neighbours.size(); i++)
            if(neighbours[i]==identity)
                return i;
        return -1;
    }
};

class ComplexNetwork{
    public:
    ComplexNetwork(std::string fname){
        this->filename=fname;
        stat0=0;
        stat1=0;
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
                Node* node1=getNode(inputNode);
                node1->addNeighbour(outputNode);
                Node* node2=getNode(outputNode);
                node2->addNeighbour(inputNode);
            }        
        }
        cout<<"Data Loaded"<<endl;
        file.close();
    }

    Node* getNode(int identity){
        if(nodeCount>identity)
            return nodeList[identity];
        cout<<"Node with id = "<<identity<<" not found";
        return NULL;
    }

    void printAllEdges(int lim){
        for(int i=0; i<nodeCount; i++){
            Node* node=nodeList[i];
            cout<<node->getId()<<" -> ";
            node->printAllNeighbours(lim);
        }
    }

    std::string getSummary(){
        std::ostringstream oss;
        oss<<stat0<<" "<<stat1;
        return oss.str();
    }

    void beginSimulation(int epochLimit, int stepCount, int volatility){
        for(int epoch=0; epoch<epochLimit; epoch++){
            for(int step=0; step<stepCount; step++){
                interact(volatility);
            }
            cout<<getSummary()<<endl;
        }
    }

    

    int nodeCount, edgeCount, stat0, stat1;
    std::vector<Node*> nodeList;
    std::string filename;

    void generateNetwork(int nodeC, int edgeC){
        this->nodeCount=nodeC;
        this->edgeCount=edgeC;
        for(int i=0; i<nodeC; i++){
            int randState=std::rand();
            if(randState%2==0)
                stat0++;
            else
                stat1++;
            Node* newNode=new Node(i, randState%2);
            this->nodeList.push_back(newNode);
        }
    }

    void interact(int volatility){
        for(int i=0; i<nodeCount; i++){
            double seed=std::rand()/RAND_MAX;
            //double seed=0.0;
            if(seed<volatility*10){
                Node* node=nodeList[i];
                for(int j=0; j<node->neighbours.size(); j++){
                    Node* tarNode=nodeList[node->neighbours[j]];
                    seed=std::rand()/RAND_MAX;
                    //seed=0;
                    if(node->getState()!=tarNode->getState() && seed<volatility*5){
                        seed=std::rand()/RAND_MAX;
                        //seed=1;
                        if(seed>0.5)
                            convince(node, tarNode);
                        else
                            rewire(node, tarNode);
                    }
                }
            }
        }
    }

    void convince(Node* inputNode, Node* outputNode){
        outputNode->changeState();
    }

    void rewire(Node* inputNode, Node* outputNode){
        inputNode->deleteNeighbour(outputNode->getId());
        outputNode->deleteNeighbour(inputNode->getId());
    }
};

int main(){
    cout<<"Hello World"<<endl;
    ComplexNetwork* network=new ComplexNetwork("../data/trial.txt");
    network->loadData();
    network->printAllEdges(100);
    cout<<endl<<endl;
    network->rewire(network->getNode(0), network->getNode(2));
    network->printAllEdges(100);
    //network->beginSimulation(1000, 10, 0.001);
}