#include <iostream>
#include <vector>
#include <algorithm>

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
        int id;
        vector<int> neighbours;
};