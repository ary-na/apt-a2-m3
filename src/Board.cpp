#include "../include/Board.h"

Board::Board() {

    // Make 2D vector.
    int vectorCol = maxCol + 1;
    int vectorRow = maxRow + 1;
    std::vector<Tile *> row(vectorCol, nullptr);
    this->boardVector = std::vector<std::vector<Tile *> >(vectorRow, row);

    // Board starts with no tiles.
    this->numOfTiles = 0;
}

Board::Board(const Board& other) {

    // Make 2D vector and copy number of tiles.
    int vectorCol = other.maxCol + 1;
    int vectorRow = other.maxRow + 1;
    std::vector<Tile*> row(vectorCol, nullptr);
    this->boardVector = std::vector<std::vector<Tile*> >(vectorRow, row);
    this->numOfTiles = other.numOfTiles;

    // Traverse board vector and copy tiles.
    if (other.numOfTiles > 0) {
        int tilesAdded = 0;
        while (tilesAdded != other.numOfTiles) {
            for (int row = this->minRow; row <= other.maxRow; row++) {
                for (int col = this->minCol; col <= other.maxCol; col++)  {
                    if (other.boardVector[row][col] != nullptr) {
                        Tile* temp = new Tile(*other.boardVector[row][col]);
                        this->boardVector[row][col] = temp;
                        temp = nullptr;
                        tilesAdded++;
                    }
                }
            }
        }
    }
}

Board::Board(Board &&other) {

    // Move board vector and number of tiles.
    this->numOfTiles = other.numOfTiles;
    this->boardVector = other.boardVector;

    // Clear other. 
    if (other.numOfTiles > 0) {
        int tilesCleared = 0;
        while (tilesCleared != other.numOfTiles) {
            for (int row = other.minRow; row <= other.maxRow; row++) {
                for (int col = other.minCol; col <= other.maxCol; col++) {
                    if (other.boardVector[row][col] != nullptr) {
                        other.boardVector[row][col] = nullptr;
                        tilesCleared++;
                    }
                }
            }
        }
    }
    other.numOfTiles = 0;
}

Board::~Board() {

    // Check if any tiles to delete.
    if (this->numOfTiles > 0) {
        int tilesDeleted = 0;

        // Traverse board vector and delete tiles
        while (tilesDeleted != this->numOfTiles) {
            for (int row = this->minRow; row <= this->maxRow; row++) {
                for (int col = this->minCol; col <= this->maxCol; col++) {
                    if (this->boardVector[row][col] != nullptr) {
                        delete this->boardVector[row][col];
                        this->boardVector[row][col] = nullptr;
                        tilesDeleted++;
                    }
                }
            }
        }
    }
}

void Board::addTileAtPos(Tile *tile, char row, int col) {

    // Convert row to number equivalent.
    row = toupper(row) - 'A';

    // Check if given position exists on the board vector.
    if ((row <= this->maxRow && row >= this->minRow) &&
        (col <= this->maxCol && col >= this->minCol)) {

        // Add tile if there isn't one at given position.
        if (this->boardVector[row][col] == nullptr) {
            this->boardVector[row][col] = tile;
        }
    }
    this->numOfTiles++;
}

void Board::eraseTileAtPos(char row, int col) {
    // Convert row to number equivalent.
    row = toupper(row) - 'A';

    // Check if given position exists on the board vector.
    if ((row <= maxRow && row >= minRow) &&
        (col <= maxCol && col >= minCol)) {

        // Erase tile if there is one at given position.
        if (this->boardVector[row][col] != nullptr) {
            this->boardVector[row][col] = nullptr;
        }
    }
    this->numOfTiles--;
}

Tile *Board::getTileAtPos(char row, int col) const {

    // Convert row to number equivalent.
    row = toupper(row) - 'A';

    // If the given row and col is out of bounds.
    if (row > this->maxRow || row < this->minRow ||
        col > this->maxCol || col < this->minCol) {
        throw std::out_of_range("Board getTileAtPos() - Out of bounds");

        // Get tile at the given row and col.
    } else {
        Tile *returnTile = this->boardVector[row][col];
        return returnTile;
    }
}

void Board::printBoard() const {

    // Print col header.
    int colHeader = this->maxCol + 1;
    int colHeaderText = this->minCol;

    for (int col = this->minCol; col <= colHeader; col++) {
        if (col == 0) {
            std::cout << "   ";
        } else {
            std::cout << colHeaderText << " ";
            if (colHeaderText < 10) {
                std::cout << " ";
            }
            colHeaderText++;
        }
    }
    std::cout << std::endl;

    // Print col header underline.
    for (int col = this->minCol; col <= colHeader; col++) {
        std::cout << "---";
    }
    std::cout << std::endl;

    // Print row header.
    char rowHeaderText = this->minRowChar;

    for (int row = this->minRow; row <= this->maxRow; row++) {
        std::cout << rowHeaderText << " |";
        ++rowHeaderText;

        // Print tiles in row.
        for (int col = this->minCol; col <= this->maxCol; col++) {
            if (this->boardVector[row][col] == nullptr) {
                std::cout << "  ";
            } else {
                std::cout << this->boardVector[row][col]->getAsStr();
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

std::vector<std::vector<Tile *> > Board::getBoardVector() const {
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

void Board::addToArray(std::string tilesArray[], int *i) {
    int tilesAdded = 0;

    // Traverse board vector, add tile if there is one.
    while (tilesAdded != this->numOfTiles) {
        for (int row = this->minRow; row <= this->maxRow; row++) {
            for (int col = this->minCol; col <= this->maxCol; col++) {
                if (this->boardVector[row][col] != nullptr) {
                    Tile *current = this->boardVector[row][col];
                    tilesArray[*i] = current->getAsStr();
                    current = nullptr;
                    (*i)++;
                    tilesAdded++;
                }
            }
        }
    }
}

std::string Board::getAsStr() {
    std::string boardStr = "";
    int tilesAdded = 0;

    // Traverse board vector, add tile if there is one.
    while (tilesAdded != this->numOfTiles) {
        for (int row = this->minRow; row <= this->maxRow; row++) {
            for (int col = this->minCol; col <= this->maxCol; col++) {
                if (this->boardVector[row][col] != nullptr) {
                    if (tilesAdded != 0) {
                        boardStr += " ,";
                    }
                    boardStr += this->boardVector[row][col]->getAsStr() +
                                "@" + (char) ('A' + row) + std::to_string(col);
                    tilesAdded++;
                }
            }
        }
    }
    return boardStr;
}