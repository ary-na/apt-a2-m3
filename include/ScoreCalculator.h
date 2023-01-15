#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H

#include <iostream>
#include "Board.h"

// Maximum sizes are dynamic, this assumes that the smallest co-ordinate will be A0
#define MIN_ROW 'A'
#define MIN_COL 0

class ScoreCalculator {
    public:
        ScoreCalculator();
        ~ScoreCalculator();

        // ** 2.3.9 Special operation: QWIRKLE! **
        // Prints the Qwirkle message, 
        // to be used if a Qwirkle is scored
        void printQwirkle() const; 

        int calculateScore(Board* board, char row, int col);
        

    private:

        int getRowScore(Board* board, char row, int col);
        int getColScore(Board* board, char row, int col);

        int getRowStart(Board* board, char row, int col);
        int getRowEnd(Board* board, char row, int col);
        int getColStart(Board* board, char row, int col);
        int getColEnd(Board* board, char row, int col);

        int checkQwirklePoints(int score);

};

#endif // SCORECALCULATOR_H