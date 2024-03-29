#include "../include/Moves.h"

Moves::Moves() : board(nullptr) {
    this->rowTiles = new LinkedList();
    this->columnTiles = new LinkedList();
}

Moves::Moves(Board *board) {
    this->board = board;
    this->rowTiles = new LinkedList;
    this->columnTiles = new LinkedList;
}

Moves::Moves(const Moves &other) {
    this->board = other.board;
    this->rowTiles = new LinkedList(*other.rowTiles);
    this->columnTiles = new LinkedList(*other.columnTiles);
}

Moves::Moves(Moves &&other) :
        board(other.board),
        rowTiles(other.rowTiles),
        columnTiles(other.columnTiles) {
    other.board = nullptr;
    other.rowTiles = nullptr;
    other.columnTiles = nullptr;
}

Moves::~Moves() {
    this->board = nullptr;
    this->rowTiles = nullptr;
    this->columnTiles = nullptr;
}

LinkedList *Moves::getRowTiles(char row, int col) {

    // This function should be called with tile coordinates.
    // It will return a linked list of tiles placed on a row.
    // This is a public function and can be called by the game
    // to validate the legal tile placement of rows.

    // Tiles direction up to down
    char rowStartUp = row + 1;

    // Tiles direction down to up
    char rowStartDown = row - 1;

    // Add tiles to linked list row while tile row + 1 does not equal to nullptr
    while (rowStartUp <= board->getMaxRowChar() &&
           board->getTileAtPos(rowStartUp, col) != nullptr) {
        this->rowTiles->addEnd(board->getTileAtPos(rowStartUp, col));
        rowStartUp++;
    }
    // Add tiles to linked list row while tile row - 1 does not equal to nullptr
    while (rowStartDown >= board->getMinRowChar() &&
           board->getTileAtPos(rowStartDown, col) != nullptr) {
        this->rowTiles->addEnd(board->getTileAtPos(rowStartDown, col));
        rowStartDown--;
    }

    return this->rowTiles;
}

LinkedList *Moves::getColumnTiles(char row, int col) {

    // This function should be called with tile coordinates.
    // It will return a linked list of tiles placed on a column.
    // This is a public function and can be called by the game
    // to validate the legal tile placement of columns.

    // Tiles direction left to right
    int columnStartLeft = col + 1;

    // Tiles direction right to left
    int columnStartRight = col - 1;

    // Add tiles to linked list col while tile column + 1 does not equal to nullptr
    while (columnStartLeft <= board->getMaxCol() &&
           board->getTileAtPos(row, columnStartLeft) != nullptr) {
        this->columnTiles->addEnd(board->getTileAtPos(row, columnStartLeft));
        columnStartLeft++;
    }
    // Add tiles to linked list col while tile column - 1 does not equal to nullptr
    while (columnStartRight >= board->getMinCol() &&
           board->getTileAtPos(row, columnStartRight) != nullptr) {
        this->columnTiles->addEnd(board->getTileAtPos(row, columnStartRight));
        columnStartRight--;
    }

    return this->columnTiles;
}

bool Moves::isTileColourMatch(const LinkedList *line, Tile *tile) {

    // This function should be called with a linked list of rows or columns and a played tile.
    // It will return a boolean value depending on whether the colour
    // of the tile played matches the tile next to it.
    // This is a public function and can be called by the game
    // to check if the colour of the tile played matches the tile next to it.

    bool match = true;

    // Traverse linked list
    for (int i = line->getLength(); i > 0; i--)
        // Check if colours match
        if (line->getAtPos(i)->colour != tile->colour)
            match = false;

    return match;
}

bool Moves::isTileShapeMatch(const LinkedList *line, Tile *tile) {

    // This function should be called with a linked list of rows or columns and a played tile.
    // It will return a boolean value depending on whether the shape
    // of the tile played matches the tile next to it.
    // This is a public function and can be called by the game
    // to check if the shape of the tile played matches the tile next to it.

    bool match = true;

    // Traverse linked list
    for (int i = line->getLength(); i > 0; i--)
        // Check if shapes match
        if (line->getAtPos(i)->shape != tile->shape)
            match = false;

    return match;
}

bool Moves::isTileExistAtLocation(char row, int col) {

    // This function should be called with tile coordinates.
    // It will return a boolean value depending on whether a tile exists at the location.
    // This is a public function and can be called by the game
    // to validate if a tile exists at a location.

    bool exists = true;

    // Tile already exists at the location
    exists = board->getTileAtPos(row, col) != nullptr;

    return exists;
}