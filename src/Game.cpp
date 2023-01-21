#include "../include/Game.h"
#include "../include/Validator.h"
#include "../include/Moves.h"

Game::Game(Player *player1, Player *player2, bool testFlag) {

    // Set the test flag.
    this->testFlag = testFlag;

    // Create the ordering for the tile bag.
    this->tileBag = new LinkedList();
    fillTileBag(this->tileBag);
    shuffleTileBag(this->tileBag);

    // Set up the initial players and their hands.
    this->player1 = player1;
    this->player2 = player2;
    fillHand(player1->getHand());
    fillHand(player2->getHand());

    // Start with empty board and player 1 starts.
    this->board = new Board();
    this->currentPlayer = player1;
    this->scoreCalculator = new ScoreCalculator();
}

Game::Game(Player* player1, Player* player2, Board* board,
           LinkedList* tileBag, Player* currentPlayer) {

    // Tile bag provided, don't activate test mode.
    this->testFlag = false;

    // Check all tiles total the correct number and type.
    bool correctTiles = checkTiles(player1->getHand(), player2->getHand(), 
                                   board, tileBag);

    if (!correctTiles) {

        // TODO: CATCH EXCEPTION
        throw std::out_of_range("Game Game() - Incorrect no. of tiles given");

    } else {
        // Load the tile bag.
        this->tileBag = tileBag;

        // Load the players and their hands.
        this->player1 = player1;
        this->player2 = player2;

        // Load the board and current player.
        this->board = board;
        this->currentPlayer = currentPlayer;
        this->scoreCalculator = new ScoreCalculator();
    }
}

Game::Game(const Game& other) {

    // Copy the test flag.
    this->testFlag = other.testFlag;

    // Copy tile bag, players, board and score calculator.
    this->tileBag = new LinkedList(*other.tileBag);
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

void Game::fillHand(LinkedList *hand) {
    while ((hand->getLength() < 6) && (this->tileBag->getLength() > 0)) {

        // When a tile is drawn from the bag, it's taken from the front.
        Tile *tileDrawn = this->tileBag->getFront();

        // When adding a tile, it's always added at the end.
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

    // Add shapes and colours to array for iteration.
    Colour colours[TOTAL_COLOURS];
    makeColoursArray(colours);
    Shape shapes[TOTAL_SHAPES];
    makeShapesArray(shapes);

    // Add 2 of each colour and shape combination to the tile bag.
    for (int i = 0; i < sizeof(colours) / sizeof(Colour); i++) {
        for (int j = 0; j <sizeof(shapes) / sizeof(Shape); j++) {
            tileBag->addEnd(new Tile(colours[i], shapes[j]));
            tileBag->addEnd(new Tile(colours[i], shapes[j]));
        }
    }
}

LinkedList* Game:: getTileBag() const {
    return this->tileBag;
}

void Game::shuffleTileBag(LinkedList *tileBag) {

    // Check if there are tiles in the tile bag.
    if (tileBag->getLength() > 0) {
        LinkedList* tempTileBag = new LinkedList();
        int totalTiles = tileBag->getLength();

        // Shuffle tiles and put in temporary tile bag.
        for (int i = 0; i < totalTiles; i++) {

            // Generate a random number between min and max.
            int min = 1;
            int max = tileBag->getLength();
            int randomVal = 0;
            std::uniform_int_distribution<int> uniform_dist(min, max);

            // If test flag is true, set seed 
            // to ensure consistent randomness.
            if(this->testFlag) {
                std::default_random_engine engine(2);
                randomVal = uniform_dist(engine);
            } else {
                std::random_device engine;
                randomVal = uniform_dist(engine);
            }
            // Get a tile from tile bag at random pos.
            Tile *randomTile = tileBag->getAtPos(randomVal);

            // Add a deep copy to the temp tile bag.
            tempTileBag->addEnd(new Tile(*randomTile));

            // Delete tile from original tile bag.
            tileBag->deleteAtPos(randomVal);
        }
        // Add tiles back to original tile bag.
        for (int i = 1; i <= totalTiles; i++) {
            tileBag->addEnd(new Tile(*tempTileBag->getAtPos(i)));
        }
        delete tempTileBag;
        tempTileBag = nullptr;
    }
}

bool Game::isComplete() const {
    bool isComplete = false;

    // A game is complete when the tile bag is empty and 
    // one of the players has no more tiles in their hand.
    if (this->tileBag->getLength() == 0 &&
       (this->player1->getHand()->getLength() == 0 ||
        this->player2->getHand()->getLength() == 0)) {
        isComplete = true;
    }
    return isComplete;
}

bool Game::isReplaceLegal(Tile *tile) const {
    bool isLegal = false;
    
    // The tile must be in the current player's hand 
    // and the the tile bag must have tiles in it.
    if (this->currentPlayer->getHand()->search(tile) &&
        this->tileBag->getLength() > 0) {
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
    if (!this->currentPlayer->getHand()->search(tile)) {
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
        this->currentPlayer->getHand()->deleteByNode(tile);
        this->tileBag->addEnd(tile);

        // Draw a new tile from the tile bag and add it to the hand.
        fillHand(this->currentPlayer->getHand());

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
        this->currentPlayer->getHand()->deleteByNode(tile);

        // Update the player’s score.
        int score = scoreCalculator->calculateScore(this->board, row, col);
        this->currentPlayer->addScore(score);

        // Draw a replacement tile from the tile bag and add it
        // to the player’s hand, if there are available tiles.
        fillHand(this->currentPlayer->getHand());

        // Continue with the other player’s turn.
        nextPlayerTurn();
    }
    return isLegal;
}

bool Game::checkTiles(LinkedList* player1Hand, LinkedList* player2Hand, 
                      Board* board, LinkedList* tileBag) {
                      
    bool correctTiles = true;
    int totalTiles = player1Hand->getLength() + player2Hand->getLength() + 
                     board->getNumOfTiles() + tileBag->getLength();
    
    // Check if there are the right number of tiles.
    if (totalTiles != this->maxTilesInGame) {
        correctTiles = false;

    // Check for 2 of each type of tile.
    } else {

        // Track array index.
        int i = 0;
  
        // Add all given tiles to a single array.
        std::string tilesArray[this->maxTilesInGame];
        fillTilesArray(tilesArray, &i, player1Hand);
        fillTilesArray(tilesArray, &i, player2Hand);
        fillTilesArray(tilesArray, &i, tileBag);
        fillTilesArray(tilesArray, &i, board);

        // Make array with all expected tiles.
        std::string expectedTilesArray[this->maxTilesInGame];
        fillExpectedTilesArray(expectedTilesArray);

        // Compare the two arrays.
        correctTiles = arraysEqual(expectedTilesArray, tilesArray);
    }
    return correctTiles;
}

void Game::fillTilesArray(std::string tilesArray[], int* i, Board* tileSource) {
    int tilesAdded = 0;

    // Stop traversing when no more tiles to add.
    while (tilesAdded != tileSource->getNumOfTiles()) {

        // Traverse board vector and add tile if there is one.
        for (int row = tileSource->getMinRow(); 
             row <= tileSource->getMaxRow(); row++) {

            for (int col = tileSource->getMinCol(); 
                 col <= tileSource->getMaxCol(); col++) {     
                          
                if (tileSource->getBoardVector()[row][col] != nullptr) {
                    Tile* current = tileSource->getBoardVector()[row][col];
                    tilesArray[*i] = current->colour + 
                                     std::to_string(current->shape);
                    (*i)++;
                    tilesAdded++;
                }
            }
        }
    }
}

void Game::fillTilesArray(std::string tilesArray[], int* i, 
                          LinkedList* tileSource) {

    // Traverse tile aource and add every tile to array.                   
    for (int j = 1; j <= tileSource->getLength(); j++) {
        tilesArray[*i] = tileSource->getAtPos(j)->colour +
                         std::to_string(tileSource->getAtPos(j)->shape);
        (*i)++;
    }
}

void Game::fillExpectedTilesArray(std::string expectedTilesArray[]) { 

    // Add shapes and colours to array for iteration.
    Colour colours[TOTAL_COLOURS];
    makeColoursArray(colours);
    Shape shapes[TOTAL_SHAPES];
    makeShapesArray(shapes);

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

void Game::makeColoursArray(Colour colours[]) {
    colours[0] = RED;
    colours[1] = ORANGE;
    colours[2] = YELLOW;
    colours[3] = GREEN;
    colours[4] = BLUE;
    colours[5] = PURPLE;
}

void Game::makeShapesArray(Shape shapes[]) {
    shapes[0] = CIRCLE;
    shapes[1] = STAR_4;
    shapes[2] = DIAMOND;
    shapes[3] = SQUARE;
    shapes[4] = STAR_6;
    shapes[5] = CLOVER;
}