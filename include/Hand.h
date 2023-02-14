#ifndef HAND_H
#define HAND_H

#include "LinkedList.h"
#include <iostream>
#include <utility>

// @author - Carelle Mulawa-Richards

class Hand {
public:
    Hand();

    Hand(const Hand &other);

    Hand(Hand &&other);

    ~Hand();

    // Returns the hand as a string.
    std::string getAsStr();

    // Returns the total tiles.
    int getNumOfTiles() const;

    // Returns true if getNumOfTiles() is 0.
    bool isEmpty();

    // Returns true if the given tile is in the hand.
    bool containsTile(Tile *tile);

    // Removes the first tile matching the given tile.
    void removeTile(Tile *tile);

    // Takes a string array and adds the tiles from the hand
    // to it. The tiles will be added to the array starting at
    // the given index. Used for checkTiles() in game.
    void addToArray(std::string tilesArray[], int *i);

    // Prints all tiles in hand.
    void printHand();

    // Adds the given tile to the end of the hand.
    void addTile(Tile *tile);

    // Returns the maximum tiles a player can have in their hand.
    int getMaxTilesInHand() const;

    LinkedList *getHandList() const;

    void setHandList(LinkedList *handList);

private:
    LinkedList *handList;
    const static int maxTilesInHand = 6;
};

#endif // HAND_H