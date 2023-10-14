#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>
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
 *      size - An integer variable which will hold the size of the neighbours' array so that it can be dynamically allocated later.
 *      state - A boolean variable which contains the state (0/1) of the node. Randomly assigned while creating the node and can change when interacting with a node which has a different state.
 *      neighbours - An integer array containing the id numbers of all of its neighbours
*/
class Node{
    public:

    int id, size;
    bool state;
    std::vector<int> neighbours;

    Node(int identity, bool status){
        this->id = identity;
        this->state = status;
        this->size=0;
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

    int getNeighbourCount(){
        return size;
    }

/**
 * This function adds a different node's id to the node's list of neighbours. 
 * Input parameter: an integer variable containing the id of the neighbouring node to be added.
 * Return Type: 0 if sucess, -1 if fail
*/
    bool addNeighbour(int newneigh){
        if(isNeighbour(newneigh)==-1) {
            this->neighbours.push_back(newneigh);
            size++;
            return true;
        }
        else{
            cout<<this->getId()<<" and "<<newneigh<<" are already neighbours"<<endl;
            return false;
        }
    }

/**
 * This function deletes an existing neighbour's id from the vector neighbours
 * Input parameter: an integer variable containing the id of the neighbouring node to be removed.
*/
    bool deleteNeighbour(int tar){
        int ind=this->isNeighbour(tar);
        if(ind>-1 && neighbours[ind]!=tar){
            cout<<"While deleting "<<tar<<" from "<<this->getId()<<" we had indexing issue"<<endl;
            return false;
        }
        if(ind>-1){
            neighbours.erase(std::remove(neighbours.begin(), neighbours.end(), tar), neighbours.end());
            size--;
            return true;
        }
        else
            cout<<"Deletion Failed on node "<<this->getId()<<" while removing neighbour "<<tar<<" and ind= "<<ind<<endl;
        return false;
    }

/**
 * This function prints all neighbours of a node. Primarily used for debugging various parts of the program.
 * Input parameter: an integer variable denoting the max number of neighbours to be printed, incase a node has a lot of neighbours
*/
    void printAllNeighbours(int lim){
        for(int i=0; i<this->size && i<lim; i++)
            cout<<this->neighbours[i]<<", ";
        cout<<endl;
    }
    void printAllNeighbours(){
        for(int i=0; i<this->size; i++)
            cout<<this->neighbours[i]<<", ";
        cout<<endl;
    }

/**
 * This function iterates through the neighbours vector to check if a given node id is present in the list.
 * Input parameter: An integer variable containing the id of the node we want to check along with a char variable 
 * Return values: Returns the location of the id being stored in the vector if it is present if option='i'; 
 *                Returns identity if option=Returns -1 if the node is not a neighbour
*/
    //returns -1 if identity is not a neighbour, else returns index number 
    int isNeighbour(int identity){
        for(int i=0; i<this->size; i++)
            if(neighbours[i]==identity)
                return i;
        return -1;
    }

/**
 * This function is meant for debugging purposes. Returns True if neighbour and false if not.
*/
    bool neighbourCheck(int identity){
        for(int i=0; i<this->size; i++)
            if(neighbours[i]==identity)
                return true;
        return false;
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
        cout<<"Constructor reached"<<endl;
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
        cout<<"Data Load Start"<<endl;
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
                if(inputNode==outputNode)
                    continue; //prevents edges into self
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
        //cout<<"Node with id = "<<identity<<" not found"<<endl;
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
        oss<<stat0<<" "<<(stat1/(stat1*1.0+stat0*1.0))<<" "<<edgeCount;
        return oss.str();
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
            int randState=getRandomNumber(100);
            if(randState%2==0)
                stat0++;
            else
                stat1++;
            Node* newNode=new Node(i, randState%2);
            this->nodeList.push_back(newNode);
        }
    }

/**
 * This function starts the simulation by calling the interact() as well as regularly printing the results after every stepCount loop.
 * Input Parameters :   epochLimit - An integer variable which defines the duration of execution of the simulation.
 *                      stepCount - An integer variable which defines the number of steps in each epoch. The total duration of the simulation = epochLimit*stepCount.
 *                      volatility - The frequency with which nodes ineract with each other.
*/
    void beginSimulation(int epochLimit, int stepCount, double volatility){
        cout<<getSummary()<<endl;
        ofstream outputFile;
        outputFile.open("../data/output001_2.txt");
        outputFile<<"Pop1 Pop2"<<endl;
        for(int epoch=0; epoch<epochLimit; epoch++){
            for(int step=0; step<stepCount; step++){
                interact(volatility);
            }
            if(epoch%10==0){
                cout<<"Epoch No. "<<epoch<<endl;
                checkInconsitentNeighbours();
            }
            cout<<getSummary()<<endl;
            outputFile << getSummary() <<endl;
        }
        outputFile.close();
    }

/**
 * This function is responsible for the interactions between the nodes, which are further controlled by convince() and rewire().
 * It iterates through every edge and uses random number generation to decide on its interaction
 * Input Parameter - An integer variable between 0 and 0.1 which controls how often an interaction occurs. 
*/
    void interact(double volatility){
        for(int i=0; i<nodeCount; i++){
            if(nodeList[i]->getNeighbourCount()==0)
                continue;
            double seed=getRandomNumber(1009);
            //double seed=0.0;
            double seed2=volatility*1009.0;
            if(seed<seed2){
                Node* node=nodeList[i];
                //cout<<"*";
                Node* tarNode=getNeighbour(node);
                if(node->getState()!=tarNode->getState()){
                    seed=getRandomNumber(1009);
                    //seed=1;
                    if(seed<=504)
                        convince(node, tarNode);
                    else
                        rewire(node, tarNode);
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
        if(outputNode->getState()){
            stat1++;
            stat0--;
        }
        else{
            stat0++;
            stat1--;
        }
    }

/**
 * This function is responsible for the deletion of an old edge and the creation of a new edge which happened as a result of interation between 2 nodes of 2 different states.
 * Input Parameters :   inputNode - pointer to the input node.
 *                      outputNode - pointer to the output node.
*/
    void rewire(Node* adderNode, Node* deleterNode){
        bool chk=true;;
        Node* newNeighbour= getNode(getRandomNewNeighbour(adderNode));
        //cout<<"Adder = "<<adderNode->getId()<<endl;
        //cout<<"New = "<<newNeighbour->getId()<<endl;
        //cout<<"Deleter = "<<deleterNode->getId()<<endl;
        //cout<<"Adder neighbours = ";
        //adderNode->printAllNeighbours();
        //cout<<"Deleter Neighbours = ";
        //deleterNode->printAllNeighbours();
        chk=adderNode->addNeighbour(newNeighbour->getId());
        // if(!chk)
        //     cout<<"3";
        chk=newNeighbour->addNeighbour(adderNode->getId());
        // if(!chk)
        //     cout<<"4";
        chk=adderNode->deleteNeighbour(deleterNode->getId());
        // if(!chk)
        //     cout<<"1";
        chk=deleterNode->deleteNeighbour(adderNode->getId()); 
        // if(!chk)
        //     cout<<"2";      
        if(!chk){
            cout<<"Error in Rewiring"<<endl;
            exit(0);
        }

    }

    int getRandomNewNeighbour(Node* node){
        int newIndex=3, indx=0;
        do{
            newIndex=getRandomNumber(nodeCount-1);
            indx=node->isNeighbour(newIndex);
            if(newIndex==node->getId()) //prevents function from randomly assigning the same to to itself. Our graph doesn't allow edges to itself.
                indx=1;
        }while(indx!=-1);
        //cout<<"Is new number "<<newIndex<<" Neighbour of "<<node->getId()<<"?"<<node->isNeighbour(newIndex)<<"  size = "<<node->getNeighbourCount()<<endl;
        return newIndex;
    }

    Node* getNeighbour(Node* node){
        //cout<<"Node Size = "<<node->getNeighbourCount()<<" for node = "<<node->getId()<<endl;
        //node->printAllNeighbours();
        int seed=getRandomNumber(node->getNeighbourCount()-1);
        //cout<<"Random Index = "<<seed<<" vs Size = "<<node->size<<endl;
        Node* n=getNode(node->neighbours[seed]);
        //cout<<"Random Neighbour = "<<n->getId()<<endl;
        
        return n;
    }

/**
 * Iterates through all the nodes and gives the number of discordant edges
 * Retrun : Integer containing the count of discordant edges
*/
    int getDiscordantEdgeCount(){
        int count=0;
        for(Node* node: nodeList){
            for(int id:node->neighbours){
                Node* neighbour=this->getNode(id);
                if(node->getState()!=neighbour->getState())
                    count++;
            }
        }
        return count;
    }

/**
 * This function generates a random number between 0 and limit, and returns it to the caller
 * Input Parameters : limit - Integer variable which will contain the upper limit of random number generation.
 * Return Value : Integer variable of a random number.
*/
    int getRandomNumber(int limit){
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0, limit); 
        return dist6(rng);
    }

    void checkInconsitentNeighbours(){
        int difference=0;
        for(Node* node: nodeList){
            for(int neigh: node->neighbours){
                Node* neighbour=this->getNode(neigh);
                if(node->neighbourCheck(neighbour->getId()) != neighbour->neighbourCheck(node->getId()))
                    difference++;
            }
        }
        cout<<"Difference = "<<difference<<endl;
    }

    void debugger(){
        Node* node1=this->getNode(5);
        Node* node2=this->getNode(node1->neighbours[1]);
        Node* node3=this->getNode(65);
        node1->printAllNeighbours();
        cout<<node1->isNeighbour(74);
        cout<<node1->isNeighbour(2);
        // node2->printAllNeighbours();
        // node3->printAllNeighbours();
        // node1->deleteNeighbour(node2->getId());
        // node2->deleteNeighbour(node1->getId());
        // node1->addNeighbour(node3->getId());
        // node3->addNeighbour(node1->getId());
        // node1->printAllNeighbours();
        // node2->printAllNeighbours();
        // node3->printAllNeighbours();
    }
};

int main(){
    ComplexNetwork* network=new ComplexNetwork("../data/facebook.txt");
    network->loadData();
    //cout<<network->getSummary()<<endl;
    //network->checkInconsitentNeighbours();
    //network->debugger();
    network->beginSimulation(10000, 20, 0.01);
    //network->printAllEdges(15);
}

//TODO: Plot number of pop vs discordant edges.