#ifndef COMPUTER_H
#define COMPUTER_H

#include "Hand.h"
#include "Board.h"
#include "Moves.h"
#include "ScoreCalculator.h"
#include "LinkedList.h"
#include "Player.h"

// @author - Arian Najafi Yamchelo

class Computer {
public:
    Computer(Player* player);

    Computer(const Computer &other);

    Computer(Computer &&other);

    ~Computer();

    void printMove();

    char getTargetRow() const;

    int getTargetCol() const;

    Colour getTileColour() const;

    Shape getTileShape() const;

    void setTargetRow(char targetRow);

    void setTargetCol(int targetCol);

    void setTileColour(Colour tileColour);

    void setTileShape(Shape tileShape);

    void setTargetScore(int targetScore);

    Hand *getHand() const;

    LinkedList *getHandTiles() const;

private:
    Hand *hand;
    LinkedList *handTiles;
    Player* player;

    char targetRow;
    int targetCol;
    Colour tileColour;
    Shape tileShape;

    int targetScore;

    const static char minTargetRow = 'A';
};


#endif //COMPUTER_H
