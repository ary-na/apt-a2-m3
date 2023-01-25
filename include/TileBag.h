#ifndef TILEBAG_H
#define TILEBAG_H

#include "LinkedList.h"
#include "Player.h"
#include <utility>
#include <string>
#include <iostream> 
#include <memory>
#include <random>

class TileBag {
    public:
        // Constructor for creating an empty tile bag. 
        // To be used when loading a game from file.
        TileBag();

        // Constructor for setting up a tile bag for a new game.
        TileBag(bool testFlag);

        TileBag(const TileBag& other);
        TileBag(TileBag&& other);
        ~TileBag();

        // Returns the linked list for the tile bag.                            // DO WE NEED THIS NOW 
        LinkedList* getTileBagList() const;                                     // WE HAVE GETASSTRING()?

        // Returns the total titles.
        int getNumOfTiles() const;

        // Returns true if getNumOfTiles() is 0.
        bool isEmpty();

        // Fills the tile bag with 72 tiles, in 
        // 6 colors and 6 shapes and 2 of each type.
        void fillTileBag();

        // Shuffles the tiles in the tile bag to 
        // make a random inital order for a new game.
        void shuffleTileBag(bool testFlag);

        // Takes a tile and adds it to the end.
        void addTile(Tile* tile);

        // Takes a player's hands and fills it
        // with up to 6 tiles from the tile bag.
        void fillHand(Hand* hand);

        // Takes a string array and fills it from the given index with
        // the tiles from the tile bag. Used in checkTiles() in a game. 
        void addToArray(std::string tilesArray[], int* i);

        // Returns the tile bag as a string.
        std::string getAsStr();

    private:
        LinkedList* tileBagList;
};

#endif // TILEBAG_H