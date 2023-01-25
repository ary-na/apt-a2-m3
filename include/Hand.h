#ifndef HAND_H
#define HAND_H

#include "LinkedList.h"
#include <iostream>
#include <utility>

class Hand {
    public:
        Hand();
        Hand(const Hand& other);
        Hand(Hand&& other);
        ~Hand();

        // Returns the hand as a string.
        std::string getAsString();

        // Returns the total titles.
        int getNumOfTiles() const;

        // Returns true if getNumOfTiles() is 0.
        bool isEmpty();

        // Returns true if the given tile is in the hand.
        bool containsTile(Tile* tile);

        // Removes the first tile matching the given tile. 
        void removeTile(Tile* tile);

        // Returns the hand list. 
        LinkedList* getHandList();

        // Takes a string array and fills it from the given index with
        // the tiles from the hand. Used in checkTiles() in a game. 
        void addToArray(std::string tilesArray[], int* i);

        // Prints all tiles in hand. 
        void printHand();
        
        // Adds the given tile to the end of the hand. 
        void addTile(Tile* tile);
        
    private:
        LinkedList* handList;
};

#endif // HAND_H