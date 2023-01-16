#include "../include/Moves.h"

Moves::Moves() : board() {
    this->rowTiles = new LinkedList();
    this->columnTiles = new LinkedList();
}

Moves::Moves(Board *board) {
    this->board = board;
    this->rowTiles = new LinkedList;
    this->columnTiles = new LinkedList;
}

Moves::~Moves() {
    this->board = nullptr;
    this->rowTiles = nullptr;
    this->columnTiles = nullptr;
}

LinkedList *Moves::getRowTiles(char row, int col) {

    // @author - Arian Najafi Yamchelo
    // This function should be called with tile coordinates.
    // It will return a linked list of tiles placed on a row.
    // This is a public function and can be called by the game to validate the legal tile placement of rows.

    // Tiles direction up to down
    char rowStartUp = row + 1;

    // Tiles direction down to up
    char rowStartDown = row - 1;

    try {
        // Add tiles to linked list row while tile row + 1 does not equal to nullptr
        while (rowStartUp <= MAX_START_ROW_CHAR && board->getTileAtPos(rowStartUp, col) != nullptr) {
            this->rowTiles->addEnd(board->getTileAtPos(rowStartUp, col));
            rowStartUp++;
        }
        // Add tiles to linked list row while tile row - 1 does not equal to nullptr
        while (rowStartDown >= MIN_START_ROW_CHAR && board->getTileAtPos(rowStartDown, col) != nullptr) {
            this->rowTiles->addEnd(board->getTileAtPos(rowStartDown, col));
            rowStartDown--;
        }
    } catch (const std::out_of_range &E) {}

    return this->rowTiles;
}

LinkedList *Moves::getColumnTiles(char row, int col) {

    // @author - Arian Najafi Yamchelo
    // This function should be called with tile coordinates.
    // It will return a linked list of tiles placed on a column.
    // This is a public function and can be called by the game to validate the legal tile placement of columns.

    // Tiles direction left to right
    int columnStartLeft = col + 1;

    // Tiles direction right to left
    int columnStartRight = col - 1;

    try {
        // Add tiles to linked list col while tile column + 1 does not equal to nullptr
        while (columnStartLeft <= MAX_START_COL_NUM && board->getTileAtPos(row, columnStartLeft) != nullptr) {
            this->columnTiles->addEnd(board->getTileAtPos(row, columnStartLeft));
            columnStartLeft++;
        }
        // Add tiles to linked list col while tile column - 1 does not equal to nullptr
        while (columnStartRight >= MIN_START_COL_NUM && board->getTileAtPos(row, columnStartRight) != nullptr) {
            this->columnTiles->addEnd(board->getTileAtPos(row, columnStartRight));
            columnStartRight--;
        }
    } catch (const std::out_of_range &E) {}
    return this->columnTiles;
}

bool Moves::isTileColourMatch(const LinkedList *line, Tile *tile) {

    // @author - Arian Najafi Yamchelo
    // This function should be called with a linked list of rows or columns and a played tile.
    // It will return a boolean value depending on whether the colour of the tile played matches the tile next to it.
    // This is a public function and can be called by the game to check if the colour of the tile played matches the tile next to it.

    bool match = true;

    // Traverse linked list
    for (int i = line->getLength(); i > 0; i--)
        // Check if colours match
        if (line->getAtPos(i)->colour != tile->colour)
            match = false;

    return match;
}

bool Moves::isTileShapeMatch(const LinkedList *line, Tile *tile) {

    // @author - Arian Najafi Yamchelo
    // This function should be called with a linked list of rows or columns and a played tile.
    // It will return a boolean value depending on whether the shape of the tile played matches the tile next to it.
    // This is a public function and can be called by the game to check if the shape of the tile played matches the tile next to it.

    bool match = true;

    // Traverse linked list
    for (int i = line->getLength(); i > 0; i--)
        // Check if shapes match
        if (line->getAtPos(i)->shape != tile->shape)
            match = false;

    return match;
}

bool Moves::isTileExistAtLocation(char row, int col) {

    // @author - Arian Najafi Yamchelo
    // This function should be called with tile coordinates.
    // It will return a boolean value depending on whether a tile exists at the location.
    // This is a public function and can be called by the game to validate if a tile exists at a location.

    bool exists = true;

    try {
        // Tile already exists at the location
        exists = board->getTileAtPos(row, col) != nullptr;
    } catch (const std::out_of_range &E) {}
    return exists;
}