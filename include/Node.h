#ifndef NODE_H
#define NODE_H

#include "Tile.h"

class Node {
    public:
        Node(Tile* tile);
        Node(const Node& other);
        ~Node();

        Tile* tile;
        Node* next;

    private:
};

#endif // NODE_H