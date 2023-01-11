#include "../include/Moves.h"

Moves::Moves(Board &board) {
    this->tileRow = new LinkedList;
    this->tileColumn = new LinkedList;
    this->board = &board;
}

Moves::~Moves() {
    delete tileRow;
    delete tileColumn;
    delete board;
}

LinkedList *Moves::getRowTiles(char row, int col) {

    // Add tiles up to down
    while (board->getTileAtPos(row++, col) != nullptr && this->tileRow->getLength() <= MAX_NUM_TILES)
        if(isTileAttributesMatch(this->tileRow, board->getTileAtPos(row++, col)))
            this->tileRow->addEnd(board->getTileAtPos(row++, col));

    // Add tiles down to up
    while (board->getTileAtPos(row--, col) != nullptr && this->tileRow->getLength() <= MAX_NUM_TILES)
        if(isTileAttributesMatch(this->tileRow, board->getTileAtPos(row--, col)))
            this->tileRow->addEnd(board->getTileAtPos(row--, col));

    return this->tileRow;
}

LinkedList *Moves::getColumnTiles(char row, int col) {

    // Add tiles left to right
    while (board->getTileAtPos(row, col++) != nullptr && this->tileColumn->getLength() <= MAX_NUM_TILES)
        if(isTileAttributesMatch(this->tileColumn, board->getTileAtPos(row, col++)))
            this->tileColumn->addEnd(board->getTileAtPos(row, col++));

    // Add tiles right to left
    while (board->getTileAtPos(row, col--) != nullptr && this->tileColumn->getLength() <= MAX_NUM_TILES)
        if(isTileAttributesMatch(this->tileColumn, board->getTileAtPos(row, col--)))
            this->tileColumn->addEnd(board->getTileAtPos(row, col--));

    return this->tileColumn;
}

bool Moves::isTileAttributesMatch(LinkedList *line, Tile *tile) {
    return line->getAtPos(line->getLength() - 1)->colour == tile->colour ||
           line->getAtPos(line->getLength() - 1)->shape == tile->shape;
}
