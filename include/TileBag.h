#ifndef TILEBAG_H
#define TILEBAG_H

#include "LinkedList.h"
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

        // Returns the linked list for the tile bag.
        LinkedList* getTileList() const;

        // Returns the total titles.
        int getNumOfTiles() const;

        // Returns true if totalTiles() is 0.
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
        void fillHand(LinkedList *hand);

        // Takes a string array and fills it from the given index with
        // the tiles from the tile bag. Used in checkTiles() in a game. 
        void fillTilesArray(std::string tilesArray[], int* i);

    private:
        LinkedList* tileList;
};

#endif // TILEBAG_H