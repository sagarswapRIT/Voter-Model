#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <string>
#include "../include/Node.hpp"

class ComplexNetwork{
    public:
    ComplexNetwork(int nodeC, int edgeC, int card);
    //virtual ~ComplexNetwork();
    //int main();
    //void generateRandomNetwork();
    Node getNode(int identity);
    void loadData(std::string filename);
    void generateNetwork(int nodeC, int edgeC);

    private:
    int nodeCount, edgeCount, cardinality;
    std::vector<Node> nodeList;
    //void connectNodes(int id1, int id2);
};