#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include "Board.h"
#include "LinkedList.h"

class Validator {
public:

public:
    Validator();

    explicit Validator(Board *board);

    ~Validator();

    const static int MAX_NUM_TILES = 6;
    const static int MIN_START_COL = 0;
    const static int MAX_START_COL = 25;
    const static int MIN_START_ROW = 'A';
    const static int MAX_START_ROW = 'Z';

    // Validate username input (Players should only consist of letters (no numbers or symbols))
    static bool isNameValid(const std::string &input);

    // Return a list of tiles added to the row
    LinkedList *getRowTiles(char row, int col);

    // Return a list of tiles added to the column
    LinkedList *getColumnTiles(char row, int col);

    // Check if the board is empty
    bool isBoardEmpty();

    // Check matching of tiles based on the colours and shapes
    bool isTileColourMatch(const LinkedList* line, Tile *tile);

    // Check matching of tiles based on the colours and shapes
    bool isTileShapeMatch(const LinkedList* line, Tile *tile);

    // Check if a tile already exists on the board
    bool isTileExistAtLocation(char row, int col);

private:
    Board *board;
    LinkedList *tileColumn;
    LinkedList *tileRow;
};

#endif // VALIDATOR_H