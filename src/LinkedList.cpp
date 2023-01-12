#include "../include/LinkedList.h"
#include <iostream>
#include <exception>

LinkedList::LinkedList() {
    this->head = nullptr;
}

LinkedList::LinkedList(const LinkedList& other) {
    // TODO
}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::clear() {
    while (this->head != nullptr) {
        deleteFront();
    }
}

void LinkedList::printList() const {
    Node* current = head;

    // Check if LinkedList is empty
    if (current == nullptr) {
        std::cout << "List is empty" << std::endl;
    
    // Otherwise traverse and print each tile
    } else {
        int count = 1;
        while (current != nullptr) {
            if (count != 1) {
                std::cout << ",";
            }
            std::cout << current->tile->colour << current->tile->shape;
            current = current->next;
            ++count;
        }
        std::cout << std::endl; 
    }
}

Tile* LinkedList::getFront() const {
    return this->head->tile;
}

Tile* LinkedList::getAtPos(int pos) const {

    // If given pos is out of bounds
    if (pos > getLength() || pos < 1 || this->head == nullptr) {

        // TODO: Catch exception
        throw std::out_of_range("LinkedList getAtPos() - Out of bounds");

    // Traverse until position is reached 
    } else {
        int count = 1;
        Node* current = this->head;
        Tile* returnTile;
        while (count <= pos) {
            if (count == pos) {
                returnTile = current->tile;
            } 
            ++count;
            current = current->next;
        }
        return returnTile;
    }
}

int LinkedList::getLength() const {
    int count = 0;
    Node* current = this->head;

    // Traverse and count each Node
    while (current != nullptr) {
        ++count;
        current = current->next;
    }
    return count;
}

bool LinkedList::search(Tile* tile) const {
    bool result = false;
    Node* current = this->head;

    // Traverse and compare each tile to the given tile
    while (current != nullptr && result == false) {
        if ((tile->colour == current->tile->colour) &&
            (tile->shape == current->tile->shape)) {
                result = true;
        }
        current = current->next;
    }
    return result;
}

void LinkedList::addEnd(Tile* tile) {
    Node* temp = new Node(tile);

    // Add tile as head if LinkedList is empty
    if (this->head == nullptr) {
        this->head = temp;

    // Traverse until end and add there
    } else {
        Node* current = this->head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = temp;
    }
}

void LinkedList::addFront(Tile* tile) {
    Node* temp = new Node(tile);

    // Add tile as head if LinkedList is empty
    if (this->head == nullptr) {
        this->head = temp;

    // Add at front of LinkedList
    } else {
        temp->next = this->head;
        this->head = temp;
    }
}

void LinkedList::deleteAtPos(int pos) {

    // If given pos is out of bounds
    if (pos > getLength() || pos < 1 || this->head == nullptr) {

        // TODO: Catch exception
        throw std::out_of_range("LinkedList deleteAtPos() - Out of bounds");
    
    // Delete the head if given pos is head
    } else if (pos == 1) {
        deleteFront();

    // Traverse LinkedList to pos and delete tile
    } else {
        Node* temp = this->head;
        Node* previous;
        while (--pos) { 
            previous = temp; 
            temp = temp->next; 
        }
        previous->next = temp->next;
        delete temp;
    }
}

void LinkedList::deleteFront() {

    // Ensure the LinkedList is not empty
    if (this->head != nullptr) {
        Node* temp = this->head;
        this->head = this->head->next;
        delete temp;
    } 
}

void LinkedList::deleteEnd() {

    // Ensure the LinkedList is not empty
    if (this->head != nullptr)  {

        // Delete the head if the end is the head
        if (this->head->next == nullptr) {
            delete this->head;
            this->head = nullptr;

        // Traverse until end and delete end 
        } else {
            Node* previous = this->head;
            while (previous->next->next != nullptr) {
                previous = previous->next;
            }
            Node* temp = previous->next;
            previous->next = nullptr;
            delete temp;
        }
    }
}

void LinkedList::deleteByNode(Tile* tile) {

    // Delete the head if given tile matches the head 
    if ((tile->colour == this->head->tile->colour) &&
        (tile->shape == this->head->tile->shape)) {
        deleteFront();

    // Traverse LinkedList until matching
    // tile is found and delete it 
    } else {
        bool result = false;
        Node* previous = this->head;
        Node* current = this->head->next;
        while (current != nullptr && result == false) {
            if ((tile->colour == current->tile->colour) &&
                (tile->shape == current->tile->shape)) {
                Node* temp = current;
                previous->next = current->next;
                delete temp;
                result = true;
            }
            current = current->next;
            previous = previous->next;
        }  
    }
}