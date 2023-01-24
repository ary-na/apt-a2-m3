#include "../include/Game.h"

Game::Game() {
    this->testFlag = false;
    this->tileBag = nullptr;
    this->player1 = nullptr;
    this->player2 = nullptr;
    this->board = nullptr;
    this->currentPlayer = nullptr;
    this->scoreCalculator = nullptr;
}

Game::Game(Player *player1, Player *player2, bool testFlag) {

    // Set the test flag.
    this->testFlag = testFlag;

    // Create the tile bag and board.
    this->tileBag = new TileBag(testFlag);
    
    // Set up the players and their hands.
    this->player1 = player1;
    this->player2 = player2;
    this->tileBag->fillHand(player1->getHand());
    this->tileBag->fillHand(player2->getHand());

    // Start with empty board and player 1 starts.
    this->board = new Board();
    this->currentPlayer = player1;
    this->scoreCalculator = new ScoreCalculator();
}

Game::Game(const Game& other) {

    // Copy tile bag, players, board and score calculator.
    this->tileBag = new TileBag(*other.tileBag);
    this->player1 = new Player(*other.player1);
    this->player2 = new Player(*other.player2);
    this->board = new Board(*other.board);
    this->scoreCalculator = new ScoreCalculator(*other.scoreCalculator);

    // Set the current player.
    if (other.currentPlayer == other.player2) {
        this->currentPlayer = this->player2;
    } else {
        this->currentPlayer = this->player1;
    }
}

Game::Game(Game&& other) {
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

void Game::loadGameData(Player* player1, Player* player2, Board* board,
           TileBag* tileBag, Player* currentPlayer) {

    // Check that given data contains a full set of tiles.
    bool correctTiles = checkTiles(player1->getHand(), player2->getHand(), 
                                   board, tileBag);

    // Create game and load data if tiles are correct.
    if (!correctTiles) {
        throw std::out_of_range("File has incorrect tiles!");
    } else {
        this->tileBag = tileBag;
        this->player1 = player1;
        this->player2 = player2;
        this->board = board;
        this->currentPlayer = currentPlayer;
        this->scoreCalculator = new ScoreCalculator();
    }
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
    if (this->currentPlayer == player1) {
        this->currentPlayer = player2;
    } else if (this->currentPlayer == player2) {
        this->currentPlayer = player1;
    }
}

TileBag* Game:: getTileBag() const {
    return this->tileBag;
}

bool Game::isComplete() const {
    bool isComplete = false;

    // A game is complete when the tile bag is empty and 
    // one of the players has no more tiles in their hand.
    if (this->tileBag->isEmpty() &&
       (this->player1->getHand()->getLength() == 0 ||                           // HAND CLASS?
        this->player2->getHand()->getLength() == 0)) {                          // HAND CLASS?
        isComplete = true;
    }
    return isComplete;
}

bool Game::isReplaceLegal(Tile *tile) const {
    bool isLegal = false;
    
    // The tile must be in the current player's hand 
    // and the the tile bag must have tiles in it.
    if (this->currentPlayer->getHand()->search(tile) &&                         // HAND CLASS?
        !this->tileBag->isEmpty()) {
        isLegal = true;
    }
    return isLegal;
}

bool Game::isPlaceLegal(Tile *tile, char row, int col) const {
    bool isLegal = true;
    std::unique_ptr<Moves> moves(new Moves(this->board));

    // Row and col to validate.
    LinkedList *validRow = moves->getRowTiles(row, col);
    LinkedList *validCol = moves->getColumnTiles(row, col);

    // The tile must be in the current player's hand.
    if (!this->currentPlayer->getHand()->search(tile)) {                        // HAND CLASS?
        isLegal = false;

    // Tile cannot be placed at a location of another tile on the board.
    } else if (moves->isTileExistAtLocation(row, col)) {
        isLegal = false;
    
    // Tiles must be placed in the same line.
    } else if (!this->getBoard()->isEmpty() && 
               validRow->getLength() == 0 && validCol->getLength() == 0) {
        isLegal = false;

    // A line can never be longer than 6 tiles.
    } else if (validRow->getLength() >= this->maxTilesInLine || 
               validCol->getLength() >= this->maxTilesInLine) {
        isLegal = false;

    // Tiles must share one colour or shape attribute.
    } else if (!(Moves::isTileColourMatch(validRow, tile) || 
                 Moves::isTileShapeMatch(validRow, tile)) && 
                 validRow->getLength() > 0) {
        isLegal = false;

    // Tiles must share one colour or shape attribute.
    } else if (!(Moves::isTileColourMatch(validCol, tile) || 
                 Moves::isTileShapeMatch(validCol, tile)) && 
                 validCol->getLength() > 0) {
        isLegal = false;

    // There cannot be duplicate tiles in a line.
    } else if (validRow->search(tile) || validCol->search(tile)) {
        isLegal = false;
    }
    return isLegal;
}

bool Game::replaceTile(Tile *tile) {
    bool isLegal = isReplaceLegal(tile);
    if (isLegal) {

        // Remove the given tile from hand and place it in the tile bag.
        this->currentPlayer->getHand()->deleteByNode(tile);                     // HAND CLASS?
        this->tileBag->addTile(tile);

        // Draw a new tile from the tile bag and add it to the hand.
        this->tileBag->fillHand(this->currentPlayer->getHand());

        // Continue with the other player’s turn.
        nextPlayerTurn();
    }
    return isLegal;
}

bool Game::placeTile(Tile *tile, char row, int col) {
    bool isLegal = isPlaceLegal(tile, row, col);
    if (isLegal) {

        // Place the tile onto the board.
        this->board->addTileAtPos(tile, row, col);
        this->currentPlayer->getHand()->deleteByNode(tile);                     // HAND CLASS?

        // Update the player’s score.
        int score = scoreCalculator->calculateScore(this->board, row, col);
        this->currentPlayer->addScore(score);

        // Draw a replacement tile from the tile bag and add it
        // to the player’s hand, if there are available tiles.
        this->tileBag->fillHand(this->currentPlayer->getHand());

        // Continue with the other player’s turn.
        nextPlayerTurn();
    }
    return isLegal;
}

bool Game::checkTiles(LinkedList* player1Hand, LinkedList* player2Hand, 
                      Board* board, TileBag* tileBag) {
                      
    bool correctTiles = true;
    int totalTiles = player1Hand->getLength() + player2Hand->getLength() + 
                     board->getNumOfTiles() + tileBag->getNumOfTiles();
    
    // Check if there are the right number of tiles.
    if (totalTiles != this->maxTilesInGame) {
        correctTiles = false;

    // Check for 2 of each type of tile.
    } else {

        // Track array index.
        int i = 0;
  
        // Add all given tiles to a single array.
        std::string tilesArray[this->maxTilesInGame];
        fillTilesArray(tilesArray, &i, player1Hand);                            // HAND CLASS?
        fillTilesArray(tilesArray, &i, player2Hand);                            // HAND CLASS?
        tileBag->fillTilesArray(tilesArray, &i);
        board->fillTilesArray(tilesArray, &i);

        // Make array with all expected tiles.
        std::string expectedTilesArray[this->maxTilesInGame];
        fillExpectedTilesArray(expectedTilesArray);

        // Compare the two arrays.
        correctTiles = arraysEqual(expectedTilesArray, tilesArray);
    }
    return correctTiles;
}

void Game::fillTilesArray(std::string tilesArray[], int* i,                     // HAND CLASS?
                          LinkedList* tileSource) {

    // Traverse tile source and add every tile to array.                   
    for (int j = 1; j <= tileSource->getLength(); j++) {
        tilesArray[*i] = tileSource->getAtPos(j)->colour +
                         std::to_string(tileSource->getAtPos(j)->shape);
        (*i)++;
    }
}

void Game::fillExpectedTilesArray(std::string expectedTilesArray[]) { 

    // Add shapes and colours to array for iteration.
    Colour colours[] = { RED, ORANGE, YELLOW, BLUE, PURPLE };
    Shape shapes[] = { CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER };

    // Track array index.
    int i = 0;

    // Add 2 of each colour and shape combination to the array.
    for (int j = 0; j < sizeof(colours) / sizeof(Colour); j++) {
        for (int k = 0; k < sizeof(shapes) / sizeof(Shape); k++) {
            expectedTilesArray[i] = colours[j] + std::to_string(shapes[k]);
            i++;
            expectedTilesArray[i] = colours[j] + std::to_string(shapes[k]);        
            i++;
        }
    }
}

bool Game::arraysEqual(std::string array1[], std::string array2[]) {  

    // Make sure both array are in same order.
    std::sort(array1, array1 + this->maxTilesInGame);
    std::sort(array2, array2 + this->maxTilesInGame);

    bool isEqual = true;
    int i = 0;

    // Linearly compare elements of both arrays.
    while (isEqual && i != this->maxTilesInGame) {
        if (array1[i] != array2[i]) {
            isEqual = false;
        }
        i++;
    }
    return isEqual;
}