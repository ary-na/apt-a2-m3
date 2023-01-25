#include "../include/LinkedList.h"

LinkedList::LinkedList() {
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}

LinkedList::LinkedList(const LinkedList& other) {
    this->length = other.length;

    // Check that the list isn't empty.
    if (other.length != 0) {

        // Deep copy head node, which will also deep
        // copy and link all next and previous nodes.
        this->head = new Node(*other.head);

        // If only one node, set the tail as head.
        if (other.length == 1) {
            this->tail = this->head;

        // Otherwise find and set the tail.
        } else {
            Node* current = this->head;
            while(current->next != nullptr) {
                current = current->next; 
            }
            this->tail = current; 
        }
    } else {
        this->head = nullptr;
        this->tail = nullptr;
    }
}

LinkedList::LinkedList(LinkedList&& other) {
    this->length = other.length; 
    this->head = other.head;
    this->tail = other.tail;
    other.length = 0;
    other.head = nullptr;
    other.tail = nullptr;
}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::clear() {
    while (this->head != nullptr) {
        deleteFront();
    }
}

std::string LinkedList::getAsString() {
    std::string listString = "";
    Node* current = this->head;
    if (current != nullptr) {
        int count = 1;
        while (current != nullptr) {
            if (count != 1) {
                listString.append(",");
            }
            listString.append(current->tile->getAsString());
            current = current->next;
            ++count;
        }
    }
    return listString;
}

void LinkedList::printList() {
    std::string listString = getAsString();
    if (this->length == 0) {
        std::cout << "Empty - No tiles left" << std::endl;
    } else {
        std::cout << getAsString() << std::endl;
    }
}

Tile* LinkedList::getFront() const {
    return this->head->tile;
}

Tile* LinkedList::getAtPos(int pos) const {

    // If given pos is out of bounds.
    if (pos > this->length || pos < 0 || this->head == nullptr) {

        // TODO: CATCH EXCEPTION
        throw std::out_of_range("LinkedList getAtPos() - Out of bounds");

    // Traverse until position is reached.
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
    return this->length;
}

bool LinkedList::search(Tile* tile) const {
    bool result = false;
    Node* current = this->head;

    // Traverse and compare each tile to the given tile.
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

    // Add tile as head if linked list is empty.
    if (this->head == nullptr) {
        this->head = temp;
        this->tail = temp;

    // Add at end of linked list.
    } else {
        temp->prev = this->tail;
        this->tail->next = temp;
        this->tail = temp;
    }
    ++this->length;
}

void LinkedList::addFront(Tile* tile) {
    Node* temp = new Node(tile);

    // Add tile as head if linked list is empty.
    if (this->head == nullptr) {
        this->head = temp;
        this->tail = temp;

    // Add at front of linked list.
    } else {
        temp->next = this->head;
        this->head->prev = temp;
        this->head = temp;
    }
    ++this->length;
}

void LinkedList::deleteAtPos(int pos) {

    // If given pos is out of bounds.
    if (pos > this->length || pos < 1 || this->head == nullptr) {

        // TODO: CATCH EXCEPTION
        throw std::out_of_range("LinkedList deleteAtPos() - Out of bounds");
    
    // Delete the head if given pos is head.
    } else if (pos == 1) {
        deleteFront();

    // Delete tail if given pos is tail.
    } else if (pos == this->length) {
        deleteEnd();

    // Traverse linked list to pos and delete.
    } else {
        Node* temp = this->head;
        while (--pos) { 
            temp = temp->next; 
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        temp = nullptr;
        --this->length;
    }
}

void LinkedList::deleteFront() {

    // Ensure the linked list is not empty.
    if (this->head != nullptr) {
        Node* temp = this->head;

        // If the head is the tail.
        if (this->length == 1) {
            this->head = nullptr;
            this->tail = nullptr;

        // Otherwise. 
        } else {
            this->head = this->head->next;
            this->head->prev = nullptr;
        }
        delete temp;
        temp = nullptr;
        --this->length;
    }
}

void LinkedList::deleteEnd() {

    // Ensure the linked list is not empty.
    if (this->head != nullptr)  {
        Node* temp = this->tail;

        // If the head is the tail.
        if (this->length == 1) {
            this->head = nullptr;
            this->tail = nullptr;

        // Otherwise.
        } else {
            this->tail = this->tail->prev;
            this->tail->next = nullptr;
        }
        delete temp;
        temp = nullptr;
        --this->length;
    }
}

void LinkedList::deleteByNode(Tile* tile) {

    // Delete the head if given tile matches the head.
    if ((tile->colour == this->head->tile->colour) &&
        (tile->shape == this->head->tile->shape)) {
        deleteFront();

    } else {
        bool result = false;
        Node* current = this->head->next;
        int pos = 2;

        // Traverse linked list.
        while (current != nullptr && result == false) {
            if ((tile->colour == current->tile->colour) &&
                (tile->shape == current->tile->shape)) {

                // Delete the first matching tile.
                if (pos == this->length) {
                    deleteEnd();
                    result = true;
                } else {
                    Node* temp = current;
                    temp->prev->next = current->next;
                    temp->next->prev = current->prev;
                    delete temp;
                    temp = nullptr;
                    --this->length;
                    result = true;
                }
            }
            current = current->next;
            ++pos;
        }  
    }
}

void LinkedList::addToArray(std::string array[], int* i) {  
    Node* current = this->head;
    while (current!= nullptr) {
        array[*i] = current->tile->getAsString();
        (*i)++;
    }
}