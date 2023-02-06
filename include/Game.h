#ifndef GAME_H
#define GAME_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "Board.h"
#include "Hand.h"
#include "LinkedList.h"
#include "Moves.h"
#include "Player.h"
#include "ScoreCalculator.h"
#include "TileBag.h"

// @author - Carelle Mulawa-Richards (unless specified)

class Game {
public:
    // Constructor for creating a game with no data. After calling
    // this, you must use loadGame() or newGame() to add the data.
    Game();

    Game(const Game& other);
    Game(Game&& other);
    ~Game();

    // To be used after Game() when loading a game from a file.
    // A game must have two players, a tile bag, board and
    // current player. Will return true if game has been loaded.
    bool loadGame(Player* player1, Player* player2, Board* board,
                  TileBag* tileBag, Player* currentPlayer);

    // A new game must have two players. The test flag
    // will be passed from main() and set accordingly.
    void newGame(Player* player1, Player* player2, bool testFlag, bool aiFlag);

    // Returns the current player.
    Player* getCurrentPlayer() const;

    // Returns player 1.
    Player* getPlayer1() const;

    // Returns player 2.
    Player* getPlayer2() const;

    // Returns the board.
    Board* getBoard() const;

    // Returns the tile bag.
    TileBag* getTileBag() const;

    // Returns the name of the player with the highest score.
    // Both player names are returned if there is a tie.
    std::string getHighestScorePlayer() const;

    // Returns true if game has ended. A game is complete when the tile
    // bag is empty and one of the players has no more tiles in their
    // hand or if both players have skipped their turn consecutively.
    bool isComplete();

    // @author - Arian Najafi Yamchelo
    // Take a tile from computer hand and find the best place on the board.
    // Call place tile to place the tile on the board.
    void computerMove();

    // Takes a tile, row (A-Z) and col (0-25). Returns true if the
    // tile has been placed from the current player's hand, their
    // score has been updated and isPlaceLegal() is also true.
    bool placeTile(Tile* tile, char row, int col);

    // Takes a tile and returns true if the tile has been replaced from
    // the current player's hand and isReplaceLegal() is also true.
    bool replaceTile(Tile* tile);

    // @author - Alex Barron
    // Toggles to the next player's turn. The current player will not score.
    // The game will be set to complete if the previous player also skipped.
    void skipTurn();

    // @author - Alex Barron
    // Returns true if both players have tiles in
    // their hands and the tile bag is empty.
    bool isSkipAvailable();

private:
    Board* board;
    Player* player1;
    Player* player2;
    Player* currentPlayer;
    TileBag* tileBag;

    // @author - Alex Barron
    // Calculates the current player's score in placeTile().
    ScoreCalculator* scoreCalculator;

    // Defines the maximum number of tiles allowed in game.
    const static int maxTilesInGame = 72;

    // @author - Alex Barron
    // When test flag is true, a random seed is set in shuffleTileBag()
    // to ensure consistent randomness. Run with "./qwirkle T" to activate.
    bool testFlag;

    // @author - Arian Najafi Yamchelo
    // When AI flag is true, you can play against computer.
    // Run with "./qwirkle --ai" to activate AI mode.
    bool aiFlag;

    // This is set to true if skipTurn() is successful.
    bool prevTurnSkipped;

    // This is set to true if the tile bag is empty and one player has no
    // tiles in their hand or both players skipped their turn consecutively.
    bool gameComplete;

    // Used after a player completes their turn to toggle
    // the current player between player 1 and player 2.
    void nextPlayerTurn();

    // Take a tile and returns true if replace is
    // legal according to the rules, otherwise false.
    // (1) The tile must be in the current player’s hand.
    // (2) The tile bag must have tiles in it.
    bool isReplaceLegal(Tile* tile) const;

    // @author - Arian Najafi Yamchelo
    // Takes a tile, row (A-Z) and col (0-25) and returns true if
    // placement is legal according to the rules, otherwise false.
    // (1) Tiles must share one colour or shape attribute.
    // (2) Tiles must be placed in the same line.
    // (3) A line can never be longer than six tiles.
    // (4) There cannot be duplicate tiles in a line.
    // (5) You cannot play two tiles that are exactly the same.
    // (6) The tile must be in the current player's hand.
    bool isPlaceLegal(Tile* tile, char row, int col) const;

    // Takes two player hands, a board and tile bag and
    // returns true if there is a correct set of tiles.
    static bool checkTiles(Hand* player1Hand, Hand* player2Hand, Board* board,
                    TileBag* tileBag);

    // Takes two string arrays and compares the values,
    // returns true if identical. Used in checkTiles().
    static bool arraysEqual(std::string array1[], std::string array2[]);

    // Takes a string array and adds every tile
    // a game should have. Used in checkTiles().
    static void addToArray(std::string expectedTilesArray[]);
};

#endif  // GAME_H