#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H

#include <iostream>
#include "Board.h"

class ScoreCalculator {
    public:
        ScoreCalculator();
        ScoreCalculator(const ScoreCalculator& other);
        // ScoreCalculator(ScoreCalculator&& other);
        ~ScoreCalculator();

        // ** 2.3.9 Special operation: QWIRKLE! **
        // Prints the Qwirkle message, 
        // to be used if a Qwirkle is scored
        void printQwirkle() const; 

        // Calculates the users score based on the state of the board and played tile
        // part of ** 2.3.5 Player Action:  Place a Tile **
        int calculateScore(Board* board, char row, int col);
        

    private:

        // Based on the played tile, calculates the score for a row - used by calculateScore
        int getRowScore(Board* board, char row, int col);
        // Based on the played tile, calculates the score for a column - used by calculateScore
        int getColScore(Board* board, char row, int col);

        // Gets the start of the row of a played tile - used by getRowScore
        int getRowStart(Board* board, char row, int col);
        // Gets the end of the row of a played tile - used by getRowScore
        int getRowEnd(Board* board, char row, int col);
        // Gets the start of the column of a played tile - used by getColScore
        int getColStart(Board* board, char row, int col);
        // Gets the end of the column of a played tile - used by getColScore
        int getColEnd(Board* board, char row, int col);

        // Checks if a played tile scores 6 for a qwirkle and adds bonus points
        int checkQwirklePoints(int score);

};

#endif // SCORECALCULATOR_H