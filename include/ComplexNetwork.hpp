#include <iostream>
#include <vector>
#include <random>
#include "../include/Node.hpp"

class ComplexNetwork{
    public:
    ComplexNetwork(int nodeC, int edgeC, int card);
    virtual ~ComplexNetwork();
    void generateNetwork();
    Node getNode(int identity);

    private:
    int nodeCount, edgeCount, cardinality;
    std::vector<Node> nodeList;
    void connectNodes(int id1, int id2);
};