#include "../include/ScoreCalculator.h"

ScoreCalculator::ScoreCalculator() {

}

ScoreCalculator::~ScoreCalculator() {

}

// TODO ALEX B
// Need to calculate the points of 1 for the first tile on the board
// Test file only works whilst the tiles are unvalidated
// Comments need cleaning
// Code needs reviewing
// Assumes only valid tiles are added, for example possible to score 7

int ScoreCalculator::calculateScore(Board* board, char row, int col) {

    // zero points totals
    int totalPoints = 0;
    int rowScore = 0;
    int colScore = 0;

    // Check if first tile on the board
    if ((board->getTileAtPos(row, col - 1) == nullptr && board->getTileAtPos(row, col + 1) == nullptr) && 
        (board->getTileAtPos(row - 1, col) == nullptr && board->getTileAtPos(row + 1, col) == nullptr))
    {
        totalPoints = 1;
    }
    

    if (board->getTileAtPos(row, col - 1) != nullptr || board->getTileAtPos(row, col + 1) != nullptr)
    {
        // get score for row
        rowScore = getRowScore(board, row, col); 
        if(rowScore == 6) {
            printQwirkle();
            rowScore += 6;
        }
        // add row score to points
        totalPoints = totalPoints + rowScore;
    }
    
    if (board->getTileAtPos(row - 1, col) != nullptr || board->getTileAtPos(row + 1, col) != nullptr)
    {
        // calculate col score
        colScore = getColScore(board, row, col);
        if(colScore == 6) {
            printQwirkle();
            colScore += 6;
        }
            
        // add col score to points
        totalPoints = totalPoints + colScore;
    }

    return totalPoints;
}

int ScoreCalculator::getRowScore(Board* board, char row, int col) {
    int rowScore = 0;
    int startCol = col;

    // Go left
    while (board->getTileAtPos(row, startCol) != nullptr)
    {
        startCol--;
        rowScore++;
        
    }
    // Go Right
    // reset start col and add one to avoid double counting placed tile
    startCol = col + 1;
    while (board->getTileAtPos(row, startCol) != nullptr)
    {
        startCol++;
        rowScore++;
    }
    return rowScore;
}

int ScoreCalculator::getColScore(Board* board, char row, int col) {
    int colScore = 0;
    int startRow = row;

    // Go Up
    while (board->getTileAtPos(startRow, col) != nullptr)
    {
        startRow--;
        colScore++;
    }

    // Go Down
    // reset start row and add one to avoid double counting placed tile
    startRow = row + 1;
    while (board->getTileAtPos(startRow, col) != nullptr)
    {
        startRow++;
        colScore++;
    }

    return colScore;
}


void ScoreCalculator::printQwirkle() const {
    std::cout << "QWIRKLE!!!" << std::endl;
    std::cout << std::endl;
}