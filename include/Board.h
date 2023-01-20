#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include <vector> 
#include <iostream>
#include <exception>

class Board {                                   
    public:

        // Default constructor:
        // starts with an empty board
        Board(); 

        // Deep copy constructor 
        Board(const Board& other);

        // Destructor 
        ~Board();

        // Prints the entire boardVector with tiles
        void printBoard() const;

        // Takes a tile pointer and adds it at a given 
        // row (between A-Z) and col (between 0-25) position
        void addTileAtPos(Tile* tile, char row, int col);

        // Takes a row (between A-Z) and col (between 0-25) and 
        // returns a tile pointer in that position on the boardVector
        Tile* getTileAtPos(char row, int col) const;

        // Returns the number of boardRows 
        int getBoardRows() const;

        // Returns the number of boardCols
        int getBoardCols() const;
        
        // Returns true if numOfTiles is < 1, otherwise false
        bool isEmpty() const;

        // Returns the number of tiles on the board vector 
        int getNumOfTiles() const;

        // Returns the 2D boardVector
        std::vector<std::vector<Tile*> > getBoardVector() const;

        int getMinCol() const;
        int getMaxCol() const;
        int getMinRow() const;
        int getMaxRow() const;
        char getMinRowChar() const;
        char getMaxRowChar() const;

    private:

        // The board is a fixed size of 26 x 26
        const static int boardRows = 26;
        const static int boardCols = 26;

        const static int minCol = 0;
        const static int maxCol = 25;
    
        const static int minRow = 0;
        const static int maxRow = 25;
        
        const static char minRowChar = (char)('A' + minRow); // This is A
        const static char maxRowChar = (char)('A' + maxRow); // This is B

        // Stores the number of tiles on the board,
        // gets updated when addTileAtPos()
        int numOfTiles;

        // A 2D vector of tile pointers
        std::vector<std::vector<Tile*> > boardVector;
};

#endif // BOARD_H