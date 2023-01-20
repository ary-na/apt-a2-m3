#include "../include/ScoreCalculator.h"

ScoreCalculator::ScoreCalculator()
{
}

ScoreCalculator::~ScoreCalculator()
{
}

int ScoreCalculator::calculateScore(Board *board, char row, int col)
{
    // @author - Alex Barron
    // This function should be called with the current board and the row and column
    // of a played tile. This will return, as int, the total score for a turn.
    // This is a public function and can be called by the game to get the players score.

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
    // @author - Alex Barron
    // This function should be called with the current board and the row and column
    // of a played tile. This will return, as int, the total score for a row.
    // This is a private function and is intended to be called by calculateScore().

    int rowScore = 0;
    // Get Start of Row Position, which column does it start at?
    int rowStartPos = getRowStart(board, row, col);
    // Get End of Row Position, which column does it end at?
    int rowEndPos = getRowEnd(board, row, col);

    // Calculate the row score by taking the start position from the end position
    rowScore = rowEndPos - rowStartPos - 1;
    // Check if its Qwirkle and if so add the bonus points
    rowScore += checkQwirklePoints(rowScore);

    return rowScore;
}

int ScoreCalculator::getColScore(Board *board, char row, int col)
{
    // @author - Alex Barron
    // This function should be called with the current board and the row and column
    // of a played tile. This will return, as int, the total score for a column.
    // This is a private function and is intended to be called by calculateScore().

    int colScore = 0;
    // Get Start of Col Position, which row does it start at?
    int colStartPos = getColStart(board, row, col);
    // Get End of Col Position, which row does it end at?
    int colEndPos = getColEnd(board, row, col);

    // Calculate the col score by taking the start position from the end position
    colScore = colEndPos - colStartPos - 1;
    // Check if its Qwirkle and if so add the bonus points
    colScore += checkQwirklePoints(colScore);

    return colScore;
}

int ScoreCalculator::getRowStart(Board *board, char row, int col)
{
    // @author - Alex Barron
    // This function should be called with the current board and the row and column
    // of a played tile. This will return, as int, the start column number for a row.
    // This is a private function and is intended to be called by getRowScore().

    // initialise start column as the current column
    int rowStartCol = col;

    // Try / Catch in case of out of range exception for board
    try
    {
        // Count back from the tile to find which location is not occupied by a tile
        while (rowStartCol >= board->getMinCol() && board->getTileAtPos(row, rowStartCol) != nullptr)
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
    // @author - Alex Barron
    // This function should be called with the current board and the row and column
    // of a played tile. This will return, as int, the end column number for a row.
    // This is a private function and is intended to be called by getRowScore().

    // Get the number of columns on the board
    int boardCols = board->getMaxCol();
    // initialise end column as the current column
    int rowEndCol = col;

    // Try / Catch in case of out of range exception for board
    try
    {
        // Count forward from the tile to find which location is not occupied by a tile
        while (rowEndCol <= boardCols && board->getTileAtPos(row, rowEndCol) != nullptr)
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
    // @author - Alex Barron
    // This function should be called with the current board and the row and column
    // of a played tile. This will return, as int, the start row number for a column. 
    // This is a char returned as int and would assume both are in the same case.
    // This is a private function and is intended to be called by getColScore().

    // initialise start row as the current row
    int colStartRow = row;

    // Try / Catch in case of out of range exception for board
    try
    {
        // Count up from the tile to find which location is not occupied by a tile
        while (colStartRow >= board->getMinRowChar() && board->getTileAtPos(colStartRow, col) != nullptr)
        // while (colStartRow >= MIN_ROW && board->getTileAtPos(colStartRow, col) != nullptr)
        {
            colStartRow--;
        }
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << "getColStart ERROR";
    }

    return colStartRow;
}

int ScoreCalculator::getColEnd(Board *board, char row, int col)
{
    // @author - Alex Barron
    // This function should be called with the current board and the row and column
    // of a played tile. This will return, as int, the end row number for a column. 
    // This is a char returned as int and would assume both are in the same case.
    // This is a private function and is intended to be called by getColScore().

    // Get the number of rows on the board
    // Add 65 to the number to start at A (Ascii A is 65)
    char boardRows = (board->getBoardRows() + 65);

    // initialise end row as the current row
    int colEndRow = row;

    // Try / Catch in case of out of range exception for board
    try
    {
        // Count down from the tile to find which location is not occupied by a tile
        while (colEndRow < boardRows && board->getTileAtPos(colEndRow, col) != nullptr)
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
    // @author - Alex Barron
    // This function should be called with the score for a row or column.
    // If the score is 6, then a set has been completed and a qwirkle is scored.
    // This will call the printQwirkle function and return a bonus 6 points.
    // This is a private function and is intended to be called by getColScore() or getRowScore().
    
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
    // @author - Carelle Mulawa-Richards
    // This function should be called if a qwirkle is scored to print the message to the screen.
    // This is a private function and is intended to be called by checkQwirklePoints().
    
    std::cout << "QWIRKLE!!!" << std::endl;
    std::cout << std::endl;
}