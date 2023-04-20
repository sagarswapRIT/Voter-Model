#include <iostream>
#include <vector>

class Node
{
    public:
        Node(int identity);
        bool getState();
        void changeState();
        int getId();
        void addNeighbour(int newneigh);
        bool isNeighbour(int id);

    private:
        bool state;
        int id; //Unique ID for every node
        std::vector<int> neighbours;
};