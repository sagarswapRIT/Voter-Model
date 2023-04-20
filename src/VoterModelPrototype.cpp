#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

/**
 * This is the main program file for Applied Data Science 1. This is made by Swapnil Sagar (ss3854@g.rit.edu) 
 * The file ccontains 2 classes: Node and ComplexNetwork. 
 * A main() exists outside both classes and is used to run the program.
*/


/**
 * This is the node class.
 * The member variables are:
 *      id - Int variable containing the id number of the node. The id can have values ranging from 0 to total Number of Nodes and is automatically assigned by the program while creating the node, stating from 0 and incrementing by 1 every time.
 *      state - A boolean variable which contains the state (0/1) of the node. Randomly assigned while creating the node and can change when interacting with a node which has a different state.
 *      neighbours - An integer vector containing the id numbers of all of its neighbours
*/
class Node{
    public:

    int id;
    bool state;
    vector<int> neighbours;

    Node(int identity, bool status){
        this->id = identity;
        this->state = status;
    }

    bool getState(){
        return this->state;
    }

/**
 * This function toggles the state of the node.
*/
    void changeState(){
        this->state = !this->getState();
    }

    int getId(){
        return this->id;
    }

/**
 * This function adds a different node's id to the node's list of neighbours. 
 * Input parameter: an integer variable containing the id of the neighbouring node to be added.
*/
    void addNeighbour(int newneigh){
        if(isNeighbour(newneigh)==-1) 
            neighbours.push_back(newneigh);
        else
            cout<<"Cannot add neighbour "<<newneigh<<"to the node "<<this->getId()<<endl;
    }

/**
 * This function deletes an existing neighbour's id from the vector neighbours
 * Input parameter: an integer variable containing the id of the neighbouring node to be removed.
*/
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

/**
 * This function prints all neighbours of a node. Primarily used for debugging various parts of the program.
 * Input parameter: an integer variable denoting the max number of neighbours to be printed, incase a node has a lot of neighbours
*/
    void printAllNeighbours(int lim){
        for(int i=0; i<this->neighbours.size() && i<lim; i++)
            cout<<this->neighbours[i]<<", ";
        cout<<endl;
    }

/**
 * This function iterates through the neighbours vector to check if a given node id is present in the list.
 * Input parameter: An integer variable containing the id of the node we want to check
 * Return values: Returns the location of the id being stored in the vector if it is present, -1 if the node is not a neighbour
*/
    //returns -1 if identity is not a neighbour, else returns index number 
    int isNeighbour(int identity){
        for(int i=0; i<this->neighbours.size(); i++)
            if(neighbours[i]==identity)
                return i;
        return -1;
    }
};

/**
 * This is the ComplexNetwork class. It creates several instances of the Node class and stores their locations by reference so that we can access every node. 
 * This class is also responsible for the interaction between the nodes in the Complex System.
 * The memeber variables are:
 *      nodeCount - An integer variable which keeps a count of the total Number of nodes in the network.
 *      edgeCount - An integer variable which keeps a count of the total number of edges in the network.
 *      stat0 - An integer variable which keeps a count of the number of nodes with state = 0
 *      stat1 - An integer variable which keeps a count of the number of nodes with state = 1
 *      nodeList - A vector of Node* type which contains pointers to every Node so that we can call them by reference.
 *      filename - A string object which contains the relative location of the data file which will be used to generate the network.
*/
class ComplexNetwork{
    public:

    int nodeCount, edgeCount, stat0, stat1;
    std::vector<Node*> nodeList;
    std::string filename;

    ComplexNetwork(std::string fname){
        this->filename=fname;
        stat0=0;
        stat1=0;
    }

/**
 * This function reads the text file which was defined while creating the object of ComplexNetwork. 
 * The first line of the file contains the nodeCount and the edgeCount.
 * It calls generateNetwork() which creates the network and sets up other parameters.
 * This function then connects the entire network by defining the edges between the nodes.
*/
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

/**
 * This function returns the reference to a node.
 * Input Parameter - An integer variable containing the id of the node to be called.
 * Return Value - A pointer to the node if it exists.
*/
    Node* getNode(int identity){
        if(nodeCount>identity)
            return nodeList[identity];
        cout<<"Node with id = "<<identity<<" not found";
        return NULL;
    }

/**
 * This function prints all the edges in the network by iterating through the nodeList and calling printAllNeighbours() for every node.
 * Input Parameter - An integer variable denoting the max number of neighbours to be printed, incase a node has a lot of neighbours
*/
    void printAllEdges(int lim){
        for(int i=0; i<nodeCount; i++){
            Node* node=nodeList[i];
            cout<<node->getId()<<" -> ";
            node->printAllNeighbours(lim);
        }
    }

/**
 * This function returns a string containing the number of nodes in each state at that particular time in the network.
*/
    std::string getSummary(){
        std::ostringstream oss;
        oss<<stat0<<" "<<stat1;
        return oss.str();
    }

/**
 * This function starts the simulation by calling the interact() as well as regularly printing the results after every stepCount loop.
 * Input Parameters :   epochLimit - An integer variable which defines the duration of execution of the simulation.
 *                      stepCount - An integer variable which defines the number of steps in each epoch. The total duration of the simulation = epochLimit*stepCount.
 *                      volatility - The frequency with which nodes ineract with each other.
*/
    void beginSimulation(int epochLimit, int stepCount, int volatility){
        for(int epoch=0; epoch<epochLimit; epoch++){
            for(int step=0; step<stepCount; step++){
                interact(volatility);
            }
            cout<<getSummary()<<endl;
        }
    }

/**
 * This function initialises the values of nodeCount, edgeCount, stat0 and stat1, creates every Node and assigns a random state to each one of them.
 * Input Parameters :   nodeC - An integer variable containing the number of nodes in the network.
 *                      edgeC - An integer variable containing the number of edges in the network.
*/
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

/**
 * This function is responsible for the interactions between the nodes, which are further controlled by convince() and rewire().
 * It iterates through every edge and uses random number generation to decide on its interaction
 * Input Parameter - An integer variable between 0 and 0.1 which controls how often an interaction occurs. 
*/
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

/**
 * This function is used to change the state of the neighbour with which our node interacted with and now hold the same state.
 * Input Parameters :   inputNode - pointer to the input node.
 *                      outputNode - pointer to the output node.
*/
    void convince(Node* inputNode, Node* outputNode){
        outputNode->changeState();
    }

/**
 * This function is responsible for the deletion of an old edge and the creation of a new edge which happened as a result of interation between 2 nodes of 2 different states.
 * Input Parameters :   inputNode - pointer to the input node.
 *                      outputNode - pointer to the output node.
*/
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