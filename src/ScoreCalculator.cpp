#include "../include/ScoreCalculator.h"

ScoreCalculator::ScoreCalculator()
{
}

ScoreCalculator::~ScoreCalculator()
{
}

// TODO ALEX B
// Fix up max / min. Should come from the board
// Comments need cleaning
// Code needs reviewing
// Assumes only valid tiles are added, for example possible to score 7

int ScoreCalculator::calculateScore(Board *board, char row, int col)
{
    int totalPoints = 0;
    // Get Scores
    int rowScore = getRowScore(board, row, col);
    int colScore = getColScore(board, row, col);

    // Catches tiles with no adjacent tiles
    if (colScore == 1 && rowScore == 1)
    {
        totalPoints = 1;
    }
    // Catches tiles added to extend a row only
    else if (colScore == 1 && rowScore > 1)
    {
        totalPoints = rowScore;
    }
    // Catches tiles added to extend a column only
    else if (colScore > 1 && rowScore == 1)
    {
        totalPoints = colScore;
    }
    // Catches tiles added which extend both a row and a column
    else
    {
        totalPoints = rowScore + colScore;
    }

    return totalPoints;
}

int ScoreCalculator::getRowScore(Board *board, char row, int col)
{
    int rowScore = 0;
    // Get Start of Row Position, which column does it start at?
    int rowStartPos = getRowStart(board, row, col);
    // Get End of Row Position, which column does it end at?
    int rowEndPos = getRowEnd(board, row, col);

    // Calculate the row score by taking the start position from the end position
    rowScore = rowEndPos - rowStartPos - 1;
    // Check if its Qwirkle and if so add the points
    rowScore += checkQwirklePoints(rowScore);

    return rowScore;
}

int ScoreCalculator::getColScore(Board *board, char row, int col)
{
    int colScore = 0;
    // Get Start of Col Position, which row does it start at?
    int colStartPos = getColStart(board, row, col);
    // Get End of Col Position, which row does it end at?
    int colEndPos = getColEnd(board, row, col);

    // Calculate the col score by taking the start position from the end position
    colScore = colEndPos - colStartPos - 1;
    // Check if its Qwirkle and if so add the points
    colScore += checkQwirklePoints(colScore);

    return colScore;
}

int ScoreCalculator::getRowStart(Board *board, char row, int col)
{
    int rowStartCol = col;
    // Try / Catch in case of out of range exception for board
    try
    {
        // Count back from the tile to find which location is not occupied by a tile
        while (rowStartCol >= MIN_COL && board->getTileAtPos(row, rowStartCol) != nullptr)
        {
            rowStartCol--;
        }
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << e.what() << '\n';
    }

    return rowStartCol;
}

int ScoreCalculator::getRowEnd(Board *board, char row, int col)
{
    int rowEndCol = col;
    // Try / Catch in case of out of range exception for board
    try
    {
        // Count forward from the tile to find which location is not occupied by a tile
        while (rowEndCol <= MAX_COL && board->getTileAtPos(row, rowEndCol) != nullptr)
        {
            rowEndCol++;
        }
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << e.what() << '\n';
    }

    return rowEndCol;
}

int ScoreCalculator::getColStart(Board *board, char row, int col)
{
    int colStartRow = row;
    // Try / Catch in case of out of range exception for board
    try
    {
        // Count up from the tile to find which location is not occupied by a tile
        while (colStartRow >= MIN_ROW && board->getTileAtPos(colStartRow, col) != nullptr)
        {
            colStartRow--;
        }
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << e.what() << '\n';
    }

    return colStartRow;
}

int ScoreCalculator::getColEnd(Board *board, char row, int col)
{
    int colEndRow = row;
    // Try / Catch in case of out of range exception for board
    try
    {
        // Count down from the tile to find which location is not occupied by a tile
        while (colEndRow <= MAX_ROW && board->getTileAtPos(colEndRow, col) != nullptr)
        {
            colEndRow++;
        }
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << e.what() << '\n';
    }

    return colEndRow;
}

int ScoreCalculator::checkQwirklePoints(int score)
{
    int points = 0;
    if (score == 6)
    {
        printQwirkle();
        points = 6;
    }
    return points;
}

void ScoreCalculator::printQwirkle() const
{
    std::cout << "QWIRKLE!!!" << std::endl;
    std::cout << std::endl;
}