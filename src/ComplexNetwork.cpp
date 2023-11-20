#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
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
 * The next 2 functions activate/inactivate the edge. This is done by making the neighbour a negative value.
 * Inorder to activate the edge, we make the neighbour a positive value again.
 * Input parameter: a positive int variable which contains the neighbour ID we want to actiave/deactivate
*/
    void inactivateEdge(int neighbour){
        for(int i=0;i<neighbours.size();i++){
            if(neighbours[i] == neighbour && neighbours[i]>=0)
                neighbours[i]*=-1;
            else if(neighbours[i] == -1*neighbour){
                cout<<"Already Inactive"<<endl;
            }
        }
    }

    void activateEdge(int neighbour){
        for(int i=0;i<neighbours.size();i++){
            if(neighbours[i] == -1*neighbour && neighbours[i]<0)
                neighbours[i]*=-1;
            else if(neighbours[i] == neighbour){
                cout<<"Already Active"<<endl;
            }
        }
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
 * This function prints all active neighbours of a node. Primarily used for debugging various parts of the program.
 * Input parameter: an integer variable denoting the max number of neighbours to be printed, incase a node has a lot of neighbours
*/
    void printAllActiveNeighbours(int lim){
        for(int i=0; i<this->size && i<lim; i++)
            if(this->neighbours[i]>=0)
                cout<<this->neighbours[i]<<", ";
        cout<<endl;
    }
    void printAllActiveNeighbours(){
        for(int i=0; i<this->size; i++)
            if(this->neighbours[i]>=0)
                cout<<this->neighbours[i]<<", ";
        cout<<endl;
    }

/**
 * This function iterates through the neighbours vector to check if a given node id is present in the list.
 * The first method checks regardless if the neighbour edge is active or not. The following method checks for active edge only.
 * Input parameter: A positive integer variable containing the id of the node we want to check along with a char variable 
 * Return values: Returns the location of the id being stored in the vector if it is present if option='i'; 
 *                Returns identity if option=Returns -1 if the node is not a neighbour
*/
    //returns -1 if identity is not a neighbour, else returns index number 
    int isNeighbour(int identity){
        for(int i=0; i<this->size; i++)
            if(neighbours[i]==identity || neighbours[i]==-1*identity)
                return i;
        return -1;
    }

    int isActiveNeighbour(int identity){
        for(int i=0; i<this->size; i++)
            if(neighbours[i]==identity && neighbours[i]>0)
                return i;
        return -1;
    }

/**
 * This function is meant for debugging purposes. Returns True if neighbour and false if not.
*/
    bool neighbourCheck(int identity){
        for(int i=0; i<this->size; i++)
            if(neighbours[i]==identity || neighbours[i]==-1*identity)
                return true;
        return false;
    }

    bool hasInactiveEdge(){
        for(int n:neighbours)
            if(n<0)
                return true;
        return false;
    }

/**
 * retuns the ID of the first in-active edge among the neighbours of this node.
 * Return Value: Returns the positive id of the in-active edge. Returns -1 if there are no inactvie edges.
*/
    int getInactiveEdgeID(){
        for(int n: neighbours){
            if(n<0)
                return n*-1;
        }
        cout<<"No Inactive Edge found";
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
    //node status as false is related to stat0 while true is related to stat1
    int nodeCount, edgeCount, stat0, stat1;
    int epochLimit, stepCount;
    double rewiringProbability, relativeSize;
    std::vector<Node*> nodeList;
    std::string inputFileName, outputFileName;

    ComplexNetwork(std::string infname, int epoch, int step, double vol, double relSize){
        cout<<"Constructor reached"<<endl;
        this->inputFileName="../data/input/"+infname+".txt";
        int n=vol*100.0;
        this->outputFileName="../data/output/"+infname+"_"+std::to_string(n)+"_"+std::to_string(getRandomNumber(1000))+".txt";
        stat0=0;
        stat1=0;
        epochLimit=epoch;
        stepCount=step;
        rewiringProbability=vol;
        relativeSize=relSize;
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
        file.open(this->inputFileName, ios::in);
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
                inputNode++;//this is done because node ids begin with 1 but uses a 0-indexed array
                outputNode++;
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
        generateSubNetwork();
    }

/**
 * This function returns the reference to a node.
 * Input Parameter - An integer variable containing the id of the node to be called.
 * Return Value - A pointer to the node if it exists.
*/
    Node* getNode(int identity){
        if(identity<0){
            cout<<"Negative node requested"<<endl;
            //identity*=-1;
        }
        if(nodeCount>=identity)
            return nodeList[identity-1];
        cout<<"Node with id = "<<identity<<" not found"<<endl;
        return nullptr;
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
 * This function returns a string containing the number of nodes in each state at that particular time in the network, its opinion density, number of discordant edges and epoch number
*/
    std::string getSummary(int epoch){
        std::ostringstream oss;
        long discEdge=this->getDiscordantEdgeCount();
        if(discEdge<=10 || discEdge<0.00025*edgeCount)
            exit(0);
        oss<<(epoch+1)<<" "<<stat0<<" "<<(stat0/(stat1*1.0+stat0*1.0))<<" "<<discEdge;
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
        for(int i=1; i<=nodeC; i++){
            int randState=getRandomNumber(100);
            int frac=2;
            if(randState%frac==0)
                stat0++;
            else
                stat1++;
            Node* newNode=new Node(i, randState%frac);
            this->nodeList.push_back(newNode);
        }
        cout<<"Network Generated"<<endl;
    }

    void generateSubNetwork(){
        for(Node* node: nodeList){
            for(int neigh: node->neighbours){
                if(neigh<0)
                    continue;
                int rando=this->getRandomNumber(100);
                if(relativeSize*50>rando){
                    Node* neighbour=this->getNode(neigh);
                    checkInactivity(node, neighbour);
                    node->inactivateEdge(neigh);
                    neighbour->inactivateEdge(node->getId());
                    checkInactivity(node, neighbour);
                }
            }
        }
        cout<<"Subnetwork Generated"<<endl;
    }

    void checkInactivity(Node* n1, Node* n2){
        int v1=-6969, v2=-6969;
        for(int x: n1->neighbours){
            if(abs(x)==n2->getId())
                v1=x;
        }
        for(int x: n2->neighbours){
            if(abs(x)==n1->getId())
                v2=x;
        }

        if(v1==-6969 || v2==-6969)
            cout<<"Neighbour actually not present"<<endl;
        else if((v1>0 && v2<0) || (v1<0 && v2>0))
            cout<<"Activations are of different signs"<<endl;
    }

/**
 * This function starts the simulation by calling the interact() as well as regularly printing the results after every stepCount loop.
 * Input Parameters :   epochLimit - An integer variable which defines the duration of execution of the simulation.
 *                      stepCount - An integer variable which defines the number of steps in each epoch. The total duration of the simulation = epochLimit*stepCount.
 *                      rewiringProbability - The frequency with which nodes ineract with each other.
*/
    void beginSimulation(){
        cout<<getSummary(-1)<<endl;
        ofstream outputFile;
        outputFile.open(this->outputFileName);
        outputFile<<"Epoch Pop Frac DiscEdge"<<endl;
        for(int epoch=0; epoch<this->epochLimit; epoch++){
            for(int step=0; step<this->stepCount; step++)
                interact();
            if(epoch%10==0){
                cout<<"Epoch No. "<<epoch<<endl;
                checkInconsitentNeighbours();
            }
            std::string summary=getSummary(epoch);
            cout<<summary<<endl;
            outputFile << summary <<endl;
        }
        outputFile.close();
    }

/**
 * This function is responsible for the interactions between the nodes, which are further controlled by convince() and rewire().
 * It iterates through every edge and uses random number generation to decide on its interaction
 * Input Parameter - An integer variable between 0 and 0.1 which controls how often an interaction occurs. 
*/
    void interact(){
        bool ideal=false;
        Node* node;
        do{
            long rand=this->getRandomNumber(this->nodeCount-1);
            rand++;
            node=this->getNode(rand);
            if(node->hasInactiveEdge() && this->hasActiveDiscordantEdge(node))
                ideal=true;
        }while(!ideal);
        int rand=this->getRandomNumber(100);
        Node* neighbour=this->getActiveDiscordantEdge(node);
        if(rand<=rewiringProbability*100)
            this->rewire(node, neighbour);
        else 
            this->convince(node, neighbour);
    }

/**
 * This function is used to change the state of the neighbour with which our node interacted with and now hold the same state.
 * Input Parameters :   inputNode - pointer to the input node.
 *                      outputNode - pointer to the output node.
*/
    void convince(Node* inputNode, Node* outputNode){
        if(inputNode->getState()==outputNode->getState()){
            cout<<"Dingus"<<endl;
            return; //no convincing needed since they have same opinion
        }
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
        if(!adderNode->hasInactiveEdge())
            return;
        Node* inactiveNode=this->getNode(adderNode->getInactiveEdgeID());
        adderNode->activateEdge(inactiveNode->getId());
        inactiveNode->activateEdge(adderNode->getId());
        adderNode->inactivateEdge(deleterNode->getId());
        deleterNode->inactivateEdge(adderNode->getId());
    }

/**
 * Iterates through all the nodes and gives the number of discordant edges
 * Retrun : Long Integer containing the count of discordant edges
*/
    long getDiscordantEdgeCount(){
        long count=0;
        for(Node* node: nodeList){
            for(int id:node->neighbours){
                if(id<0)
                    id*=-1;
                Node* neighbour=this->getNode(id);
                if(node->getState()!=neighbour->getState())
                    count++;
            }
        }
        return count/2;
    }

/**
 * Checks if a node has an active discordant edge.
 * Input Parameter: Node reference of the node you want to check.
 * Return Type: Boolean value True if there is an active discordant edge, else false.
*/
    bool hasActiveDiscordantEdge(Node* node){
        for(int neigh: node->neighbours){
            if(neigh<0)
                continue;
            Node* n=this->getNode(neigh);
            if(n->getState()!=node->getState())
                return true;
        }
        return false;
    }

/**
 * Returns the node reference of a node with an active discordant edge with the given node.
 * Input Parameter: Node reference of the node whose neighbour we want.
 * Return Type: Node reference of node with actvie discordant edge.
*/
    Node* getActiveDiscordantEdge(Node* node){
        for(int neigh: node->neighbours){
            if(neigh<0)
                continue;
            Node* n=this->getNode(neigh);
            if(n->getState()!=node->getState())
                return n;
        }
        return nullptr;
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
                if(neigh<0)
                    neigh*=-1;
                Node* neighbour=this->getNode(neigh);
                if(node->neighbourCheck(neighbour->getId()) != neighbour->neighbourCheck(node->getId()))
                    difference++;
            }
        }
        cout<<"Difference = "<<difference<<endl;
    }
};

int main(){
    ComplexNetwork* network=new ComplexNetwork("facebook_medium", 100000, 500, 0.8, 0.8);
    network->loadData();
    network->beginSimulation();
    cout<<"Completed"<<endl;
}

//TODO: Plot number of pop vs discordant edges.