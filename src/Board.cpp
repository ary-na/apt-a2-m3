#include "../include/Board.h"

Board::Board() {
    
    // Make 2D vector.
    std::vector<Tile*> row(this->maxCol + 1, nullptr);
    this->boardVector = std::vector<std::vector<Tile*> >(this->maxRow + 1, row);

    // Board starts with no tiles.
    this->numOfTiles = 0;
}

Board::Board(const Board& other) {

    // Make 2D vector.
    std::vector<Tile*> row(other.maxCol + 1, nullptr);
    this->boardVector = std::vector<std::vector<Tile*> >(other.maxRow + 1, row);

    // Set the number of tiles. 
    this->numOfTiles = other.numOfTiles;

    // Check if there are tiles on the board.
    if (other.numOfTiles > 0) {
        int tilesAdded = 0;

        // Stop traversing when no more tiles to add.
        while (tilesAdded != other.numOfTiles) {
            
            // Traverse board vector and copy tile if there is one.
            for (int row = this->minRow; row <= other.maxRow; row++) {
                for (int col = this->minCol; col <= other.maxCol; col++)  {
                    if (other.boardVector[row][col] != nullptr) {
                        Tile* temp = new Tile(*other.boardVector[row][col]);
                        this->boardVector[row][col] = temp;
                        ++tilesAdded;
                    }
                }
            }
        }
    }
}

Board::~Board() {
    
    // Check if there are any tiles to delete.
    if (this->numOfTiles > 0) {
        int tilesDeleted = 0;

        // Stop traversing when no more tiles to delete.
        while (tilesDeleted != this->numOfTiles) {

            // Traverse boardVector and delete tile if there is one.
            for (int row = this->minRow; row <= this->maxRow; row++) {
                for (int col = this->minCol; col <= this->maxCol; col++)  {
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

    // Convert row to number equivalent.
    row = toupper(row) - 'A';

    // Check if given position exists on the board vector.
    if ((row <= this->maxRow && row >= this->minRow) && 
        (col <= this->maxCol && col >= this->minCol)) {

        // Add Tile if there isn't one at given position.
        if (this->boardVector[row][col] == nullptr) {
            this->boardVector[row][col] = tile;
        }
    }
    ++this->numOfTiles;
}

Tile* Board::getTileAtPos(char row, int col) const {

    // Convert row to number equivalent.
    row = toupper(row) - 'A'; 

    // If the given row and col is out of bounds.
    if (row > this->maxRow || row < this->minRow || 
        col > this->maxCol || col < this->minCol) {
        
        // TODO: CATCH EXCEPTION
        throw std::out_of_range("Board getTileAtPos() - Out of bounds");

    // Get the tile at the given row and col.
    } else {
        Tile* returnTile = this->boardVector[row][col];
        return returnTile;
    }
}

void Board::printBoard() const {

    // Print col header.
    int colHeader = this->minCol;
    for (int col = this->minCol; col <= this->maxCol + 1; col++) {
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

    // Print col header underline.
    for (int col = this->minCol; col <= this->maxCol + 1; col++) {
        std::cout << "---";
    }
    std::cout << std::endl;

    // Print row header.
    char rowHeader = this->minRowChar;
    for (int row = this->minRow; row <= this->maxRow; row++) {
        std::cout << rowHeader << " |";
        ++rowHeader;

        // Print tiles in row.
        for (int col = this->minCol; col <= this->maxCol; col++) {   
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

std::vector<std::vector<Tile*> > Board::getBoardVector() const {
    return this->boardVector;
}

int Board::getMinCol() const {
    return this->minCol;
}

int Board::getMaxCol() const {
    return this->maxCol;
}

int Board::getMinRow() const {
    return this->minRow;
}
int Board::getMaxRow() const {
    return this->maxRow;
}

char Board::getMinRowChar() const {
    return this->minRowChar;
}

char Board::getMaxRowChar() const {
    return this->maxRowChar;
}