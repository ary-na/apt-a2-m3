#ifndef MOVES_H
#define MOVES_H

#include "Board.h"
#include "LinkedList.h"

class Moves {
    public:
        Moves();
        explicit Moves(Board *board);
        Moves(const Moves& other);
        Moves(Moves&& other);
        ~Moves();

        // Returns a list of tiles added to a row
        LinkedList *getRowTiles(char row, int col);

        // Returns a list of tiles added to a column
        LinkedList *getColumnTiles(char row, int col);

        // Check matching of tiles based on the colours
        static bool isTileColourMatch(const LinkedList *line, Tile *tile);

        // Check matching of tiles based on the shapes
        static bool isTileShapeMatch(const LinkedList *line, Tile *tile);

        // Check if a tile already exist on the board
        bool isTileExistAtLocation(char row, int col);

    private:
        Board *board;
        LinkedList *columnTiles;
        LinkedList *rowTiles;
};

#endif //MOVES_H
