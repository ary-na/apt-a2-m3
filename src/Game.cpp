#include "../include/Game.h"
#include "../include/Validator.h"
#include "../include/Moves.h"

Game::Game(Player *player1, Player *player2) {

    // Create the ordering for the tile bag
    this->tileBag = new LinkedList();
    fillTileBag(this->tileBag);
    shuffleTileBag(this->tileBag);

    // Set up the initial players and their hands
    this->player1 = player1;
    this->player2 = player2;
    fillHand(player1->getHand());
    fillHand(player2->getHand());

    // Start with empty board and player 1 starts
    this->board = new Board();
    this->currentPlayer = player1;
    this->scoreCalculator = new ScoreCalculator();
}

Game::Game(Player *player1, Player *player2, Board *board,
           LinkedList *tileBag, Player *currentPlayer) {

    // TODO: Check all tiles are there

    // bool correctTiles = checkTiles();
    bool correctTiles = true;

    if (!correctTiles) {

        // TODO: Catch exception
        // TODO: Throw exception

    } else {
        // Load the tile bag
        this->tileBag = tileBag;

        // Load the players and their hands
        this->player1 = player1;
        this->player2 = player2;

        // Load the board and current player
        this->board = board;
        this->currentPlayer = currentPlayer;
        this->scoreCalculator = new ScoreCalculator();
    }
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

Player *Game::getCurrentPlayer() const {
    return this->currentPlayer;
}

void Game::setCurrentPlayer(Player *player) {
    this->currentPlayer = player;
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

    // Check if player 1 has the highest score
    if (this->player1->getScore() > this->player2->getScore()) {
        winner = this->player1->getName();

        // Check if player 2 has the highest score
    } else if (this->player1->getScore() < this->player2->getScore()) {
        winner = this->player2->getName();

        // If both players have the same score
    } else {
        winner = this->player1->getName() + " and " + this->player2->getName();
    }
    return winner;
}

void Game::fillHand(LinkedList *hand) {
    while ((hand->getLength() < 6) && (this->tileBag->getLength() > 0)) {

        // When a tile is drawn from the bag, it's taken from the front
        Tile *tileDrawn = this->tileBag->getFront();

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

void Game::fillTileBag(LinkedList *tileBag) {

    // Add shapes and colours to array for iteration
    Colour colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    Shape shapes[] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

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

void Game::shuffleTileBag(LinkedList *tileBag) {

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
            Tile *randomTile = tileBag->getAtPos(randomVal);

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

void Game::setTileBag(LinkedList *tileBag) {
    this->tileBag = tileBag;
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

bool Game::isReplaceLegal(Tile *tile) const {
    bool isLegal = false;
    if (this->currentPlayer->getHand()->search(tile) &&
        this->tileBag->getLength() > 0) {
        isLegal = true;
    }
    return isLegal;
}

bool Game::isPlaceLegal(Tile *tile, char row, int col) const {

    bool isLegal = true;
    Moves *moves = new Moves(this->getBoard());

    // Row to validate
    LinkedList *validRow = moves->getRowTiles(row, col);

    // Column to validate
    LinkedList *validCol = moves->getColumnTiles(row, col);

    // The tile must be in the current player's hand
    if (!currentPlayer->getHand()->search(tile))
        isLegal = false;
    // Tile cannot be placed at a location of another tile on the board
    else if (moves->isTileExistAtLocation(row, col))
        isLegal = false;
    // Tiles must be placed in the same line
    else if (!this->getBoard()->isEmpty() && validRow->getLength() == 0 && validCol->getLength() == 0)
        isLegal = false;
    // A line can never be longer than six tiles
    else if (validRow->getLength() >= Moves::MAX_NUM_TILES_IN_A_LINE || validCol->getLength() >= Moves::MAX_NUM_TILES_IN_A_LINE)
        isLegal = false;
    // Tiles must share one colour or shape attribute
    else if (!(Moves::isTileColourMatch(validRow, tile) || Moves::isTileShapeMatch(validRow, tile)) && validRow->getLength() > 0)
        isLegal = false;
    // Tiles must share one colour or shape attribute
    else if (!(Moves::isTileColourMatch(validCol, tile) || Moves::isTileShapeMatch(validCol, tile)) && validCol->getLength() > 0)
        isLegal = false;
    // There cannot be duplicate tiles in a line
    else if (validRow->search(tile) || validCol->search(tile))
        isLegal = false;

    delete moves;
    return isLegal;
}

bool Game::replaceTile(Tile *tile) {
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

bool Game::placeTile(Tile *tile, char row, int col) {
    bool isLegal = isPlaceLegal(tile, row, col);
    if (isLegal) {

        // Place the tile onto the board
        this->board->addTileAtPos(tile, row, col);
        this->currentPlayer->getHand()->deleteByNode(tile);

        // Update the player’s score
        int score = scoreCalculator->calculateScore(this->board, row, col);
        this->currentPlayer->addScore(score);

        // Draw a replacement tile from the tile bag and add it
        // to the player’s hand, if there are available tiles
        fillHand(this->currentPlayer->getHand());

        // Continue with the other player’s turn
        nextPlayerTurn();
    }
    return isLegal;
}

// Delete, just for testing. 
LinkedList *Game::GetTileBag() {
    return this->tileBag;
}