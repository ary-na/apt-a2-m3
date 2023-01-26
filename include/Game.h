#ifndef GAME_H
#define GAME_H

#include "LinkedList.h"
#include "Player.h"
#include "Board.h"
#include "TileBag.h"
#include "ScoreCalculator.h"
#include "Hand.h"
#include "Moves.h"
#include <string>
#include <iostream> 
#include <memory>
#include <utility>
#include <algorithm>

class Game {
    public:
        // Constructor for loading a game. Creates a game with no data. 
        // After calling this constructor, you must use loadGame().
        Game();

        // Constructor for making a new game. A game must have two players. 
        Game(Player* player1, Player* player2, bool testFlag); 

        Game(const Game& other);
        Game(Game&& other);
        ~Game();

        // To be used after Game() when loading a game from a file. A game 
        // must have two players, a tile bag, board and current player.
        void loadGameData(Player* player1, Player* player2, Board* board, 
                          TileBag* tileBag, Player* currentPlayer); 
        
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

        // Returns true if game has ended. A game ends when the tile  
        // bag is empty and one player has no tiles in their hand.
        bool isComplete() const;

        // Takes a tile, row (A-Z) and col (0-25). Returns true if the 
        // tile has been placed from the current player's hand, their 
        // score has been updated and isPlaceLegal() is also true. 
        bool placeTile(Tile* tile, char row, int col); 

        // Takes a tile and returns true if the tile has been replaced from 
        // the current player's hand and isReplaceLegal() is also true.
        bool replaceTile(Tile* tile); 
        
    private:
        Board* board;  
        Player* player1;
        Player* player2;
        Player* currentPlayer;
        TileBag* tileBag; 

        // Calculates the current player's score in placeTile().
        ScoreCalculator* scoreCalculator;

        // Defines tile numbers for the game. 
        const static int maxTilesInGame = 72;
        const static int maxTilesInLine = 6;

        // When test flag is true, a random seed is set during 
        // shuffleTileBag() to ensure consistent randomness. 
        // Run with "./qwirkle T" to activate test mode.
        bool testFlag;

        // Used after a player completes their turn to toggle
        // the current player between player 1 and player 2.
        void nextPlayerTurn();

        // Take a tile and returns true if replace is 
        // legal according to the rules, otherwise false.
        // (1) The tile must be in the current player’s hand.
        // (2) The tile bag must have tiles in it.
        bool isReplaceLegal(Tile* tile) const;

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
        bool checkTiles(Hand* player1Hand, Hand* player2Hand, 
                        Board* board, TileBag* tileBag);

        // Helper function for checkTiles(). Takes two string arrays and
        // compares the values, returns true if identical, otherwise false.
        bool arraysEqual(std::string array1[], std::string array2[]);
        
        // Helper function for checkTiles(). Takes a string array and
        // fills it with the correct number and combination of tiles.
        void fillExpectedTilesArray(std::string expectedTilesArray[]);
};

#endif // GAME_H