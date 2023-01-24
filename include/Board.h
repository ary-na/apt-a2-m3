#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include <vector> 
#include <iostream>
#include <exception>
#include <utility>

class Board {                                   
    public:
        // Default constructor for stating 
        // a game with an empty board. 
        Board(); 

        Board(const Board& other);
        Board(Board&& other);
        ~Board();

        // Prints the entire board vector.
        void printBoard() const;

        // Takes a tile  and adds it at a given 
        // row (A-Z) and col (0-25) position.
        void addTileAtPos(Tile* tile, char row, int col);

        // Takes a row (A-Z) and col (0-25) and returns 
        // the tile in that position in the board vector.
        Tile* getTileAtPos(char row, int col) const;
        
        // Returns true if the board has no tiles.
        bool isEmpty() const;

        // Returns the number of tiles in the board vector.
        int getNumOfTiles() const;

        // Takes a string array and fills it from the given index 
        // with the tiles from a board. Used for checkTiles() in game. 
        void fillTilesArray(std::string tilesArray[], int* i);

        // Returns the 2D board vector.
        std::vector<std::vector<Tile*> > getBoardVector() const;

        // Returns the min and max index values for  
        // the rows and cols in the board vector.
        int getMinCol() const;
        int getMaxCol() const;
        int getMinRow() const;
        int getMaxRow() const;
        char getMinRowChar() const;
        char getMaxRowChar() const;

    private:
        // Defines the min and max index values for  
        // the rows and cols in the board vector.
        const static int minCol = 0;
        const static int maxCol = 25;
        const static int minRow = 0;
        const static int maxRow = 25; 
        const static char minRowChar = (char)('A' + minRow); // This is A
        const static char maxRowChar = (char)('A' + maxRow); // This is B

        // Stores the number of tiles on the board.
        // This gets updated when addTileAtPos(). 
        int numOfTiles;

        // A 2D vector of tiles.
        // The board is a fixed size of 26 x 26.
        std::vector<std::vector<Tile*> > boardVector;
};

#endif // BOARD_H