#ifndef MOVES_H
#define MOVES_H

#include "LinkedList.h"
#include "Board.h"

class Moves {
public:
    explicit Moves(Board &board);

    ~Moves();

    // Return a list of tiles added to the row
    LinkedList *getRowTiles(char row, int col);

    // Return a list of tiles added to the row
    LinkedList *getColumnTiles(char row, int col);

private:
    Board *board;
    LinkedList *tileColumn;
    LinkedList *tileRow;
    const static int MAX_NUM_TILES = 6;

    // Check matching of tiles based on the colours and shapes
    static bool isTileAttributesMatch(LinkedList *line, Tile *tile);
};

#endif //MOVES_H
