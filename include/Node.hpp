#include <iostream>
#include <vector>

class Node
{
    public:
        Node(int identity);
        virtual ~Node();
        bool getState();
        void changeState();
        int getId();
        void addNeighbour(int newneigh);
    

    private:
        bool state;
        int id; //Unique ID for every node
        std::vector<int> neighbours;
};