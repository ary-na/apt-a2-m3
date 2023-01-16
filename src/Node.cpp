#include "../include/Node.h"

Node::Node(Tile* tile) {
    this->tile = tile;
    this->next = nullptr;
    this->prev = nullptr;
}

Node::Node(const Node& other) {
    this->tile = new Tile(*other.tile);
    this->next = other.next;
    this->prev = other.prev;
}

Node::~Node() {
    delete this->tile;
    this->tile = nullptr;
}