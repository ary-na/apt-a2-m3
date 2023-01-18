#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>
#include <exception>


class LinkedList {
    public:

        // Default constructor
        LinkedList();

        // Deep copy constructor 
        LinkedList(const LinkedList& other);

        // Destructor
        ~LinkedList();
        
        // Delete every tile in the LinkedList
        void clear(); 

        // Print each tile in the LinkedList
        void printList() const; 

        // Returns head of LinkedList
        Tile* getFront() const;
        
        // Takes a pos (must be > 0 and < length)
        // and returns a pointer to the tile at the pos
        Tile* getAtPos(int pos) const; 

        // Returns total number of tiles in LinkedList
        int getLength() const; 

        // Takes a pointer to a tile and returns true if 
        // exists in the LinkedList, otherwise false 
        bool search(Tile* tile) const; 

        // Takes a pointer to a tile and 
        // adds it to the end of the LinkedList
        void addEnd(Tile* tile); 

        // Takes a pointer to a tile and 
        // adds it to the front of the LinkedList
        void addFront(Tile* tile); 

        // Takes a pos (must be > 0 and < length)
        // and deletes the tile at that pos
        void deleteAtPos(int pos); 

        // Deletes the tile at the 
        // front of the LinkedList
        void deleteFront(); 

        // Deletes the tile at the 
        // end of the LinkedList
        void deleteEnd();

        // Takes a tile pointer and removes the
        // first matching tile in the LinkedList
        void deleteByNode(Tile* tile); 

    private:
        Node* head;
        Node* tail;
        int length;
};

#endif // LINKEDLIST_H