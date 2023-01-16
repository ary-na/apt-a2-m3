#include "../include/Validator.h"
#include <regex>

Validator::Validator() : board() {
    this->tileRow = new LinkedList();
    this->tileColumn = new LinkedList();
}

Validator::Validator(Board *board) {
    this->tileRow = new LinkedList;
    this->tileColumn = new LinkedList;
    this->board = board;
}

Validator::~Validator() {
    this->tileRow = nullptr;
    this->tileColumn = nullptr;
    this->board = nullptr;
}

bool Validator::isNameValid(const std::string &input) {

    // @author - Arian Najafi Yamchelo
    // This function should be called with a string parameter.
    // It will return a boolean value depending on the string input.
    // This is a public function and can be called from the controller to validate username input.

    return std::regex_match(input, std::regex("[A-Z]+"));
}

LinkedList *Validator::getRowTiles(char row, int col) {

    // @author - Arian Najafi Yamchelo
    // This function should be called with tile coordinates.
    // It will return a linked list of tiles placed on a row.
    // This is a public function and can be called by the game to validate the legal tile placement of rows.

    // Tiles up to down
    char rowStartUp = row + 1;

    // Tiles down to up
    char rowStartDown = row - 1;

    try {
        // Add tiles to linked list row while tile row + 1 does not equal to nullptr
        while (rowStartUp <= MAX_START_ROW && board->getTileAtPos(rowStartUp, col) != nullptr) {
            this->tileRow->addEnd(board->getTileAtPos(rowStartUp, col));
            rowStartUp++;
        }
        // Add tiles to linked list row while tile row - 1 does not equal to nullptr
        while (rowStartDown >= MIN_START_ROW && board->getTileAtPos(rowStartDown, col) != nullptr) {
            this->tileRow->addEnd(board->getTileAtPos(rowStartDown, col));
            rowStartDown--;
        }
    } catch (const std::out_of_range &E) {}

    return this->tileRow;
}

LinkedList *Validator::getColumnTiles(char row, int col) {

    // @author - Arian Najafi Yamchelo
    // This function should be called with tile coordinates.
    // It will return a linked list of tiles placed on a column.
    // This is a public function and can be called by the game to validate the legal tile placement of columns.

    // Tiles left to right
    int columnStartLeft = col + 1;

    // Tiles right to left
    int columnStartRight = col - 1;

    try {
        // Add tiles to linked list col while tile column + 1 does not equal to nullptr
        while (columnStartLeft <= MAX_START_COL && board->getTileAtPos(row, columnStartLeft) != nullptr) {
            this->tileColumn->addEnd(board->getTileAtPos(row, columnStartLeft));
            columnStartLeft++;
        }
        // Add tiles to linked list col while tile column - 1 does not equal to nullptr
        while (columnStartRight >= MIN_START_COL && board->getTileAtPos(row, columnStartRight) != nullptr) {
            this->tileColumn->addEnd(board->getTileAtPos(row, columnStartRight));
            columnStartRight--;
        }
    } catch (const std::out_of_range &E) {}
    return this->tileColumn;
}

bool Validator::isBoardEmpty() {

    // @author - Arian Najafi Yamchelo
    // This function does not take any parameters.
    // It will return a boolean value depending on whether the board is empty or not.
    // This is a public function and can be called by the game to check if the board is empty.

    bool empty = true;

    // Traverse boardVector
    for (int row = 0; row < this->board->getBoardVector().size(); row++) {
        for (int col = 0; col < this->board->getBoardVector()[row].size(); col++) {
            // Check if board is empty
            if (this->board->getBoardVector()[row][col] != nullptr)
                empty = false;

        }
    }
    return empty;
}

bool Validator::isTileColourMatch(const LinkedList *line, Tile *tile) {

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

bool Validator::isTileShapeMatch(const LinkedList *line, Tile *tile) {

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

bool Validator::isTileExistAtLocation(char row, int col) {

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

bool Validator::isSavedFileExist(std::string fileName) {
    std::string path = "savedGames/" + fileName + ".txt";

    std::fstream infile;
    infile.open(path);

    // Check if file exist 
    if(!infile.is_open()) {
        return false;

    }
    
    infile.close();
    return true;
}


bool Validator::isPlayerNameValid (std::string playerName) {
    return playerName.length()== 0 ? false : std::regex_match(playerName, std::regex("^[A-Za-z]+$"));
}