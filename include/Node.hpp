#include <iostream>
#include <vector>
#include <algorithm>

class Node
{
    public:
        Node();
        virtual ~Node();
        int getState();
        void changeState();
        int getId();

    

    private:
        int state;
        int id;
        Node* neighbours;
};