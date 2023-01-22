#ifndef NODE_H
#define NODE_H

#include "Tile.h"
#include <iostream>

class Node {
    public:
        Node(Tile* tile);
        Node(const Node& other);
        Node(Node&& other);
        ~Node();

        Tile* tile;
        Node* next;
        Node* prev;
        
    private:
};

#endif // NODE_H