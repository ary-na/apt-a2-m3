#include "../include/Game.h"
#include "../include/Computer.h"

Game::Game() {
    this->testFlag = false;
    this->aiFlag = false;
    this->tileBag = nullptr;
    this->player1 = nullptr;
    this->player2 = nullptr;
    this->board = nullptr;
    this->currentPlayer = nullptr;
    this->scoreCalculator = nullptr;
    this->prevTurnSkipped = false;
}

Game::Game(const Game &other) {

    // Copy tile bag, players, board and score calculator.
    this->testFlag = other.testFlag;
    this->aiFlag = other.aiFlag;
    this->tileBag = new TileBag(*other.tileBag);
    this->player1 = new Player(*other.player1);
    this->player2 = new Player(*other.player2);
    this->board = new Board(*other.board);
    this->scoreCalculator = new ScoreCalculator(*other.scoreCalculator);
    this->prevTurnSkipped = other.prevTurnSkipped;

    // Set the current player.
    if (other.currentPlayer == other.player2) {
        this->currentPlayer = this->player2;
    } else {
        this->currentPlayer = this->player1;
    }
}

Game::Game(Game &&other) {
    this->testFlag = other.testFlag;
    other.testFlag = false;
    this->aiFlag = other.aiFlag;
    other.aiFlag = false;
    this->player1 = other.player1;
    other.player1 = nullptr;
    this->player2 = other.player2;
    other.player2 = nullptr;
    this->currentPlayer = other.currentPlayer;
    other.currentPlayer = nullptr;
    this->scoreCalculator = other.scoreCalculator;
    other.scoreCalculator = nullptr;
    this->board = other.board;
    other.board = nullptr;
    this->tileBag = other.tileBag;
    other.tileBag = nullptr;
    this->prevTurnSkipped = other.prevTurnSkipped;
    other.prevTurnSkipped = false;
}

Game::~Game() {
    delete this->player1;
    this->player1 = nullptr;
    delete this->player2;
    this->player2 = nullptr;
    this->currentPlayer = nullptr;
    delete this->scoreCalculator;
    this->scoreCalculator = nullptr;
    delete this->board;
    this->board = nullptr;
    delete this->tileBag;
    this->tileBag = nullptr;
}

void Game::newGame(Player *player1, Player *player2, bool testFlag, bool aiFlag) {

    // Set the test flag.
    this->testFlag = testFlag;

    // Set the AI flag.
    this->aiFlag = aiFlag;

    // Create the tile bag and board.
    this->tileBag = new TileBag();
    this->tileBag->newGameTileBag(testFlag);

    // Set up the players and their hands.
    this->player1 = player1;
    this->player2 = player2;
    this->tileBag->fillHand(player1->getHand());
    this->tileBag->fillHand(player2->getHand());

    // Start with empty board and player1 starts.
    this->board = new Board();
    this->currentPlayer = player1;
    this->scoreCalculator = new ScoreCalculator();
}

bool Game::loadGame(Player *player1, Player *player2, Board *board,
                    TileBag *tileBag, Player *currentPlayer) {

    // Check that given data contains a full set of tiles.
    bool correctTiles = checkTiles(player1->getHand(), player2->getHand(),
                                   board, tileBag);

    // Create game and load data if tiles are correct.
    if (correctTiles) {
        this->tileBag = tileBag;
        this->player1 = player1;
        this->player2 = player2;
        this->board = board;
        this->currentPlayer = currentPlayer;
        this->scoreCalculator = new ScoreCalculator();
    }
    return correctTiles;
}

Player *Game::getCurrentPlayer() const {
    return this->currentPlayer;
}

Player *Game::getPlayer1() const {
    return this->player1;
}

Player *Game::getPlayer2() const {
    return this->player2;
}

Board *Game::getBoard() const {
    return this->board;
}

std::string Game::getHighestScorePlayer() const {
    std::string winner = "";

    // Check if player 1 has the highest score.
    if (this->player1->getScore() > this->player2->getScore()) {
        winner = this->player1->getName();

        // Check if player 2 has the highest score.
    } else if (this->player1->getScore() < this->player2->getScore()) {
        winner = this->player2->getName();

        // If both players have the same score.
    } else {
        winner = this->player1->getName() + " and " + this->player2->getName();
    }
    return winner;
}

void Game::nextPlayerTurn() {

    if (aiFlag) {
        this->currentPlayer = player1;
    } else {
        if (this->currentPlayer == player1) {
            this->currentPlayer = player2;
        } else if (this->currentPlayer == player2) {
            this->currentPlayer = player1;
        }
    }
}

TileBag *Game::getTileBag() const {
    return this->tileBag;
}

bool Game::isComplete() {

    // A game is complete when the tile bag is empty and one player has no
    // tiles in their hand or both players skipped their turn consecutively.
    if (!this->gameComplete && this->tileBag->isEmpty() &&
        (this->player1->getHand()->isEmpty() ||
         this->player2->getHand()->isEmpty())) {
        this->gameComplete = true;
    }
    return this->gameComplete;
}

bool Game::isReplaceLegal(Tile *tile) const {
    bool isLegal = false;

    // The tile must be in the current player's hand
    // and the tile bag must have tiles in it.
    if (this->currentPlayer->getHand()->containsTile(tile) &&
        !this->tileBag->isEmpty()) {
        isLegal = true;
    }
    return isLegal;
}

void Game::skipTurn() {
    if (isSkipAvailable()) {
        nextPlayerTurn();
        if (prevTurnSkipped) {
            this->gameComplete = true;
        } else {
            this->prevTurnSkipped = true;
        }
    }
}

bool Game::isSkipAvailable() {
    bool skipAvailable = false;
    if (this->tileBag->isEmpty()) {
        skipAvailable = true;
    }
    return skipAvailable;
}

bool Game::replaceTile(Tile *tile) {

    // Check if replace is legal according to the rules.
    bool isLegal = isReplaceLegal(tile);

    if (isLegal) {
        // Remove the given tile from hand and place it in the tile bag.
        this->currentPlayer->getHand()->removeTile(tile);
        this->tileBag->addTile(tile);

        // Draw a new tile from the tile bag and add it to the hand.
        this->tileBag->fillHand(this->currentPlayer->getHand());

        // Continue with the other player’s turn.
        nextPlayerTurn();
        this->prevTurnSkipped = false;
    }
    return isLegal;
}

void Game::computerMove() {
    this->currentPlayer = player2;
    Computer *computer = new Computer(this->currentPlayer);

    // Traverse boardVector
    for (int row = 0; row < this->board->getBoardVector().size(); row++) {
        for (int col = 0; col < this->board->getBoardVector()[row].size(); col++) {
            for (int i = 0; i < computer->getHand()->getNumOfTiles(); i++) {
                bool placeLegal = this->isPlaceLegal(computer->getHandTiles()->getAtPos(i),
                                                     Computer::minTargetRow + row, col);
                if (placeLegal) {
                    this->board->addTileAtPos(computer->getHandTiles()->getAtPos(i),
                                              Computer::minTargetRow + row, col);
                    int temp = scoreCalculator->calculateScore(this->board, Computer::minTargetRow + row, col);
                    this->board->eraseTileAtPos(Computer::minTargetRow + row, col);
                    if (temp >= computer->getTargetScore()) {
                        computer->setTargetScore(temp);
                        computer->setTileColour(computer->getHandTiles()->getAtPos(i)->colour);
                        computer->setTileShape(computer->getHandTiles()->getAtPos(i)->shape);
                        computer->setTargetRow(Computer::minTargetRow + row);
                        computer->setTargetCol(col);
                    }
                }
            }
        }
    }

    computer->printMove();
    Tile *tile = new Tile(computer->getTileColour(), computer->getTileShape());
    placeTile(tile, computer->getTargetRow(), computer->getTargetCol());
    delete computer;
    computer = nullptr;
}


bool Game::isPlaceLegal(Tile *tile, char row, int col) const {
    bool isLegal = true;
    Moves *moves = new Moves(this->board);

    try {
        // Row and col to validate.
        LinkedList *validRow = moves->getRowTiles(row, col);
        LinkedList *validCol = moves->getColumnTiles(row, col);

        // The tile must be in the current player's hand.
        if (!this->currentPlayer->getHand()->containsTile(tile)) {
            isLegal = false;

            // Tile cannot be placed at a location of another tile on the board.
        } else if (moves->isTileExistAtLocation(row, col)) {
            isLegal = false;

            // Tiles must be placed in the same line.
        } else if (!this->getBoard()->isEmpty() &&
                   validRow->getLength() == 0 && validCol->getLength() == 0) {
            isLegal = false;

            // Tiles must share one colour or shape attribute.
            // A line can never be longer than 6 tiles.
        } else if (!(Moves::isTileColourMatch(validRow, tile) ||
                     Moves::isTileShapeMatch(validRow, tile)) &&
                   validRow->getLength() > 0) {
            isLegal = false;

            // Tiles must share one colour or shape attribute.
            // A line can never be longer than 6 tiles.
        } else if (!(Moves::isTileColourMatch(validCol, tile) ||
                     Moves::isTileShapeMatch(validCol, tile)) &&
                   validCol->getLength() > 0) {
            isLegal = false;

            // There cannot be duplicate tiles in a line.
        } else if (validRow->search(tile) || validCol->search(tile)) {
            isLegal = false;
        }

        validRow = nullptr;
        validCol = nullptr;

        // If exception occurs during checks.
    } catch (std::out_of_range &e) {
        throw std::out_of_range("Program error, can't check tile placement!");
    }
    delete moves;
    moves = nullptr;
    return isLegal;
}


bool Game::placeTile(Tile *tile, char row, int col) {

    // Check if the placement is legal according to the rules.
    bool isLegal = this->isPlaceLegal(tile, row, col);

    if (isLegal) {
        // Place the tile on the board.
        this->board->addTileAtPos(tile, row, col);
        this->currentPlayer->getHand()->removeTile(tile);

        // Update the player’s score.
        int score = scoreCalculator->calculateScore(this->board, row, col);
        this->currentPlayer->addScore(score);

        // If the tile bag isn't empty, draw replacement and add to hand.
        this->tileBag->fillHand(this->currentPlayer->getHand());

        // Continue with the other player’s turn.
        nextPlayerTurn();
        this->prevTurnSkipped = false;
    }
    return isLegal;
}

bool Game::checkTiles(Hand *player1Hand, Hand *player2Hand, Board *board, TileBag *tileBag) {

    bool correctTiles = true;

    int totalTiles = player1Hand->getNumOfTiles() + board->getNumOfTiles() + player2Hand->getNumOfTiles() +
                     tileBag->getNumOfTiles();

    // Check if there are the right number of tiles.
    if (totalTiles != maxTilesInGame) {
        correctTiles = false;

        // Check for 2 of each type of tile.
    } else {

        // Track array index.
        int i = 0;

        // Add all given tiles to a single array.
        std::string tilesArray[maxTilesInGame];
        player1Hand->addToArray(tilesArray, &i);
        player2Hand->addToArray(tilesArray, &i);
        tileBag->addToArray(tilesArray, &i);
        board->addToArray(tilesArray, &i);

        // Make array with all expected tiles.
        std::string expectedTilesArray[maxTilesInGame];
        addToArray(expectedTilesArray);

        // Compare the two arrays.
        correctTiles = arraysEqual(expectedTilesArray, tilesArray);
    }
    return correctTiles;
}

void Game::addToArray(std::string expectedTilesArray[]) {

    // Add shapes and colours to array for iteration.
    Colour colours[] = {COLOURS};
    Shape shapes[] = {SHAPES};

    // Track array index.
    int i = 0;

    // Add 2 of each colour and shape combination to the array.
    for (char colour: colours) {
        for (int shape: shapes) {
            expectedTilesArray[i] = colour + std::to_string(shape);
            i++;
            expectedTilesArray[i] = colour + std::to_string(shape);
            i++;
        }
    }
}

bool Game::arraysEqual(std::string array1[], std::string array2[]) {

    // Make sure both array are in same order.
    std::sort(array1, array1 + maxTilesInGame);
    std::sort(array2, array2 + maxTilesInGame);

    bool isEqual = true;
    int i = 0;

    // Linearly compare elements of both arrays.
    while (isEqual && i != maxTilesInGame) {
        if (array1[i] != array2[i]) {
            isEqual = false;
        }
        i++;
    }
    return isEqual;
}