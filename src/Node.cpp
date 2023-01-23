#include "../include/Node.h"

Node::Node(Tile* tile) {
    this->tile = tile;
    this->next = nullptr;
    this->prev = nullptr;
}

Node::Node(const Node& other) {
    
    // Deep copy tile.
    this->tile = new Tile(*other.tile);
    
    // Deep copy and link all next nodes.
    Node* current = other.next;
    while (current != nullptr) {
        Node* temp = new Node(new Tile(*current->tile));
        temp->prev = this;
        this->next = temp;
        current = current->next;
    }
    
    // Deep copy and link all previous nodes.
    current = other.prev;
    while (current != nullptr) {
        Node* temp = new Node(new Tile(*current->tile));
        temp->next = this;
        this->prev = temp;
        current = current->prev;
    }
}

Node::Node(Node&& other) {
    this->tile = other.tile;
    this->next = other.next;
    this->prev = other.prev;
    other.tile = nullptr;
    other.next = nullptr;
    other.prev = nullptr;
}

Node::~Node() {
    delete this->tile;
    this->tile = nullptr;
}