#ifndef BOARD_H
#define BOARD_H

#include <vector> 
#include "Tile.h"

class Board {                                   
    public:

        // Constructor for when a new game is created,
        // the board starts with no tiles placed
        Board(); 

        ~Board();

        // Prints the entire boardVector with tiles
        void printBoard() const;

        // Takes a tile pointer and adds it at a given 
        // row (between A-Z) and col (between 0-25) position
        void addTileAtPos(Tile* tile, char row, int col);

        // Takes a row (between A-Z) and col (between 0-25) and 
        // returns a tile pointer in that position on the boardVector
        Tile* getTileAtPos(char row, int col) const;

    private:

        // The board is a fixed size of 26 x 26
        int boardRows;
        int boardCols;

        // A 2D vector of tile pointers
        std::vector<std::vector<Tile*> > boardVector;
};

#endif // BOARD_H