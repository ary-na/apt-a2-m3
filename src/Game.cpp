#include "../include/Game.h"

Game::Game(Player* player1, Player* player2) {
    
    // Create the ordering for the tile bag
    this->tileBag = new LinkedList();
    fillTileBag(this->tileBag);
    shuffleTileBag(this->tileBag);

    // Set up the initial player hands
    this->player1 = player1;
    this->player2 = player2;
    fillHand(player1->getHand());
    fillHand(player2->getHand());

    // Start with empty board and player 1 starts
    this->board = new Board();
    this->currentPlayer = player1;
    this->scoreCalculator = new ScoreCalculator();
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

Player* Game::getCurrentPlayer() const {
    return this->currentPlayer;
}

Player* Game::getPlayer1() const {
    return this->player1;
}

Player* Game::getPlayer2() const {
    return this->player2;
}

Board* Game::getBoard() const {
    return this->board;    
}

std::string Game::getHighestScorePlayer() const {
    std::string winner = "";
    if (this->player1->getScore() > this->player2->getScore()) {
        winner = this->player1->getName();
    } else if (this->player1->getScore() < this->player2->getScore()) {
        winner = this->player2->getName();
    } else {
        winner = this->player1->getName() + " and " + this->player2->getName();
    }
    return winner;
}

void Game::fillHand(LinkedList* hand) {
    while ((hand->getLength() < 6) && (this->tileBag->getLength() > 0)) { 

        // When a tile is drawn from the bag, it's taken from the front
        Tile* tileDrawn = this->tileBag->getFront();

        // When adding a tile, it's always added at the end 
        hand->addEnd(new Tile(*tileDrawn));

        tileBag->deleteFront();
    }
}

void Game::nextPlayerTurn() {
    if (this->currentPlayer == player1) {
        this->currentPlayer = player2;
    } else if (this->currentPlayer == player2) {
        this->currentPlayer = player1;
    }
}

void Game::fillTileBag(LinkedList* tileBag) {

    // Add shapes and colours to array for iteration
    Colour colours[] = { RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE };
    Shape shapes[] = { CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER };

    int coloursLength = sizeof(colours) / sizeof(Colour);
    int shapesLength = sizeof(shapes) / sizeof(Shape);

    // Add 2 of each colour and shape combination to the tileBag
    for (int i = 0; i < coloursLength; i++) {
        for (int j = 0; j < shapesLength; j++) {
            tileBag->addEnd(new Tile(colours[i], shapes[j]));
            tileBag->addEnd(new Tile(colours[i], shapes[j]));
        }
    }
}

void Game::shuffleTileBag(LinkedList* tileBag) {

    // Check if there are tiles in the tileBag
    if (tileBag->getLength() > 0) {

        std::unique_ptr<LinkedList> tempTileBag(new LinkedList);

        int totalTiles = tileBag->getLength();

        // Shuffle tiles and put in temporary tile bag
        for (int i = 0; i < totalTiles; i++) {
            
            // Generate a random number between min and max
            int min = 1;
            int max = tileBag->getLength();
            
            // FOR TESTING: Use default_random_engine below
            // instead of random_device to give predictable value
            // std::default_random_engine engine(2);

            std::random_device engine;
            std::uniform_int_distribution<int> uniform_dist(min, max);
            int randomVal = uniform_dist(engine);

            // Get a tile from tileBag at random pos
            Tile* randomTile = tileBag->getAtPos(randomVal);
            
            // Add a deep copy to the tempTileBag
            tempTileBag->addEnd(new Tile(*randomTile));

            // Delete tile from original tileBag
            tileBag->deleteAtPos(randomVal);
        }
        // Add tiles back to original tile bag
        for (int i = 1; i <= totalTiles; i++) {
            tileBag->addEnd(new Tile(*tempTileBag->getAtPos(i)));
        }
    }
}

bool Game::isComplete() const {
    bool isComplete = false;
    if (this->tileBag->getLength() == 0 && 
       (this->player1->getHand()->getLength() == 0 || 
        this->player2->getHand()->getLength() == 0)) {
        isComplete = true;
    }
    return isComplete;
}

bool Game::isReplaceLegal(Tile* tile) const {
    bool isLegal = false;
    if (this->currentPlayer->getHand()->search(tile) &&
        this->tileBag->getLength() > 0) {
            isLegal = true;
    }
    return isLegal;
}

// [ARIAN] TODO: Check place is legal according to the rules:
// https://www.ultraboardgames.com/qwirkle/game-rules.php
// (1) Tiles must share one colour or shape attribute 
// (2) Tiles must be placed in the same line
// (3) A line can never be longer than six tiles
// (4) There cannot be duplicate tiles in a line
// (5) You cannot play two tiles that are exactly the same
// (6) The tile must be in the current player's hand

bool Game::isPlaceLegal(Tile* tile, char row, int col) const {
    bool isLegal = true;
    return isLegal;
}

bool Game::replaceTile(Tile* tile) {
    bool isLegal = isReplaceLegal(tile);
    if (isLegal) { 

        // Remove the given tile from the hand and place it in the tileBag
        this->currentPlayer->getHand()->deleteByNode(tile);
        this->tileBag->addEnd(tile);

        // Draw a new tile from the tileBag and add it to the hand
        fillHand(this->currentPlayer->getHand());

        // Continue with the other player’s turn
        nextPlayerTurn();
    }
    return isLegal;
}

bool Game::placeTile(Tile* tile, char row, int col) {
    bool isLegal = isPlaceLegal(tile, row, col);
    if (isLegal) { 

        // Place the tile onto the board
        this->board->addTileAtPos(tile, row, col);
        this->currentPlayer->getHand()->deleteByNode(tile);

        // [ALEX] TODO: Calculate the score and assign to score variable

        // Update the player’s score
        int score = 0;
        score = scoreCalculator->calculateScore(this->board, row, col);
        this->currentPlayer->addScore(score);

        // Draw a replacement tile from the tile bag and add it
        // to the player’s hand, if there are available tiles
        fillHand(this->currentPlayer->getHand());

        // Continue with the other player’s turn
        nextPlayerTurn();
    } 
    return isLegal;
}