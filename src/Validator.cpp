#include "../include/Validator.h"
#include <regex>

// TODO: Fix out of range exception for board boundaries

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
    return std::regex_match(input, std::regex("[A-Z]+"));
}

LinkedList *Validator::getRowTiles(char row, int col) {

    // Add tiles up to down
    char rowStartUp = row + 1;
    while (board->getTileAtPos(rowStartUp, col) != nullptr) {
        this->tileRow->addEnd(board->getTileAtPos(rowStartUp, col));
        rowStartUp++;
    }

    // Add tiles down to up
    char rowStartDown = row - 1;
    while (board->getTileAtPos(rowStartDown, col) != nullptr) {
        this->tileRow->addEnd(board->getTileAtPos(rowStartDown, col));
        rowStartDown--;
    }

    return this->tileRow;
}

LinkedList *Validator::getColumnTiles(char row, int col) {

    // Add tiles left to right
    int columnStartLeft = col + 1;
    while (board->getTileAtPos(row, columnStartLeft) != nullptr) {
        this->tileColumn->addEnd(board->getTileAtPos(row, columnStartLeft));
        columnStartLeft++;
    }

    // Add tiles right to left
    int columnStartRight = col - 1;
    while (board->getTileAtPos(row, columnStartRight) != nullptr) {
        this->tileColumn->addEnd(board->getTileAtPos(row, columnStartRight));
        columnStartRight--;
    }

    return this->tileColumn;
}

bool Validator::isBoardEmpty() {

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

    bool match = true;

    // Traverse linked list
    for (int i = line->getLength(); i > 0; i--)
        // Check if colours match
        if (line->getAtPos(i)->colour != tile->colour)
            match = false;

    return match;
}

bool Validator::isTileShapeMatch(const LinkedList *line, Tile *tile) {

    bool match = true;

    // Traverse linked list
    for (int i = line->getLength(); i > 0; i--)
        // Check if shapes match
        if (line->getAtPos(i)->shape != tile->shape)
            match = false;

    return match;
}
