#include "../include/Board.h"

Board::Board() {
    
    // Make 1D vector 
    std::vector<Tile*> row(this->boardCols, nullptr);

    // Make 2D vector
    this->boardVector = std::vector<std::vector<Tile*> >(this->boardRows, row);

    // Board starts with no tiles on it
    this->numOfTiles = 0;

    // Don't need to set board size, it is 
    // fixed 26 x 26 for base gameplay 
}

Board::~Board() {
    
    // Check if there are any tiles to delete
    if (this->numOfTiles > 0) {
        int tilesDeleted = 0;

        // Stop traversing when no more tiles to delete
        while (tilesDeleted != this->numOfTiles) {

            // Traverse boardVector
            for (int row = 0; row < this->boardRows; row++) {
                for (int col = 0; col < this->boardCols; col++)  {

                    // Delete tile if there is one
                    if (this->boardVector[row][col] != nullptr) {
                        delete this->boardVector[row][col];
                        this->boardVector[row][col] = nullptr;
                        ++tilesDeleted;
                    }
                }   
            }
        }
    }
}

void Board::addTileAtPos(Tile* tile, char row, int col) {

    // Convert row to number equivalent
    row = toupper(row) - 'A';

    // Check if given position exists on the boardVector
    if ((row < this->boardRows && row >= 0) && 
        (col < this->boardCols && col >= 0)) {

        // Add Tile if there isn't one at given position
        if (this->boardVector[row][col] == nullptr) {
            this->boardVector[row][col] = tile;
        }
    }
    ++this->numOfTiles;
}

Tile* Board::getTileAtPos(char row, int col) const {

    // Convert row to number equivalent
    row = toupper(row) - 'A'; 

    // If the given row and col is out of bounds
    if (row >= this->boardRows || row < 0 || 
        col >= this->boardCols || col < 0) {
        
        // TODO: Need to catch exception
        throw std::out_of_range("Board getTileAtPos() - Out of bounds");

    // Get the tile at the given row and col
    } else {
        Tile* returnTile = this->boardVector[row][col];
        return returnTile;
    }
}

void Board::printBoard() const {

    // Print col header 
    int colHeader = 0;
    for (int col = 0; col <= this->boardCols; col++) {
        if (col == 0) {
            std::cout << "   ";
        } else {
            std::cout << colHeader << " ";
            if (colHeader < 10) {
                std::cout << " ";
            }
            ++colHeader;
        }
    }
    std::cout << std::endl;

    // Print col header underline 
    for (int col = 0; col <= this->boardCols; col++) {
        std::cout << "---";
    }
    std::cout << std::endl;

    // Print row header
    char rowHeader = 'A';
    for (int row = 0; row < this->boardRows; row++) {
        std::cout << rowHeader << " |";
        ++rowHeader;

        // Print tiles in row
        for (int col = 0; col < this->boardCols; col++)  {   
            if (this->boardVector[row][col] == nullptr) {
                std::cout << "  ";
            } else {
                std::cout << this->boardVector[row][col]->colour
                          << this->boardVector[row][col]->shape;
            } 
            std::cout << "|";
        }
        std::cout << std::endl;
    }
}

int Board::getBoardRows() const {
    return this->boardRows;
}

int Board::getBoardCols() const {
    return this->boardCols;
}

bool Board::isEmpty() const {
    bool isEmpty = true;
    if (this->numOfTiles > 0) {
        isEmpty = false;
    }
    return isEmpty;
}

int Board::getNumOfTiles() const {
    return this->numOfTiles;
}

const std::vector<std::vector<Tile *> > &Board::getBoardVector() const {
    return this->boardVector;
}
