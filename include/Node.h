#ifndef NODE_H
#define NODE_H

#include "Tile.h"
#include <iostream>

class Node {
    public:

        // Constructor for new nodes:
        // takes a tile pointer 
        Node(Tile* tile);

        // Shallow copy constructor 
        Node(const Node& other);

        // Destructor 
        ~Node();

        Tile* tile;
        Node* next;
        Node* prev;
        
    private:
};

#endif // NODE_H