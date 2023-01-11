#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H

#include <iostream>
#include "Board.h"

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

};

#endif // SCORECALCULATOR_H