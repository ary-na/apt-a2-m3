#ifndef NODE_H
#define NODE_H

#include "Tile.h"
#include <iostream>
#include <utility>

// @author - Carelle Mulawa-Richards

class Node {
    public:
        Node(Tile* tile);

        // Deep copies node, including it's next and prev nodes. 
        // This is used for the linked list copy constructor. 
        Node(const Node& other);

        Node(Node&& other);
        ~Node();

        Tile* tile;
        Node* next;
        Node* prev;
        
    private:
};

#endif // NODE_H