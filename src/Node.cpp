#include "../include/Node.h"
#include <iostream>

Node::Node(Tile* tile) {
    this->tile = tile;
    this->next = nullptr;
}

Node::Node(const Node& other) {
    this->tile = new Tile(*other.tile);
    this->next = other.next;
}

Node::~Node() {
    delete this->tile;
    this->tile = nullptr;
}