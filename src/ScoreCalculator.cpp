#include "../include/ScoreCalculator.h"

ScoreCalculator::ScoreCalculator() {

}

ScoreCalculator::~ScoreCalculator() {

}

int ScoreCalculator::calculateScore(Board* board, char row, int col) {

    // zero points totals
    int totalPoints = 0;
    int rowScore = 0;
    int colScore = 0;

    std::cout << "Calculating Score" << std::endl;

    // get score for row
    rowScore = getRowScore(board, row, col); 

    // add row score to points
    totalPoints = totalPoints + rowScore;

    // calculate col score
    colScore = getColScore(board, row, col);

    // add col score to points
    totalPoints = totalPoints + colScore;

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
    int startRow = (int)row;

    // Go Up
    while (board->getTileAtPos((char)startRow, col) != nullptr)
    {
        startRow--;
        colScore++;
    }

    // Go Down
    // reset start row and add one to avoid double counting placed tile
    startRow = (int)row + 1;
    while (board->getTileAtPos((char)startRow, col) != nullptr)
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