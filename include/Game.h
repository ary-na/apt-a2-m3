#ifndef GAME_H
#define GAME_H

#include "LinkedList.h"
#include "Player.h"
#include "Board.h"
#include "ScoreCalculator.h"

#include <string>
#include <iostream> 
#include <memory>
#include <random>

class Game {
    public:

        // ** 2.3.10 Special operation: Starting a new game **
        // Constructor specifically starting a new game:
        // takes two player pointers and sets up a new game
        Game(Player* player1, Player* player2); 

        // Constructor specifically loading a game:
        // takes pointers to two players, a tiles bag, board 
        // and current player and sets up the existing game
        Game(Player* player1, Player* player2, Board* board, 
             LinkedList* tileBag, Player* currentPlayer); 

        // Destructor
        ~Game();
        
        // Returns the currentPlayer pointer 
        Player* getCurrentPlayer() const;

        // Set Current Player 
        void setCurrentPlayer(Player* player);

        // Returns the player1 pointer  
        Player* getPlayer1() const;

        // Returns the player2 pointer 
        Player* getPlayer2() const;

        // Returns the board pointer 
        Board* getBoard() const;

        // Returns the name of the player with the highest score,
        // both player names are returned if there is a tie
        std::string getHighestScorePlayer() const;

        // Takes a player's hand pointer and fills 
        // it with up to 6 tiles from the tileBag
        void fillHand(LinkedList* hand);

        // Returns true if game has ended, otherwise false:
        // a game ends when the tileBag is empty and
        // one player has no tiles in their hand, 
        bool isComplete() const;

        // ** 2.3.5 Player action: place a tile **
        // Takes a tile pointer, row (between A-Z) and col (between 0-25), 
        // and returns true if tile has been placed from the current player's 
        // hand and their score has been updated, otherwise false:
        // a tile can only be placed if isPlaceLegal() is true
        bool placeTile(Tile* tile, char row, int col); 

        // ** 2.3.6 Player action: replace a tile **
        // Takes a tile pointer and returns true if the tile has been 
        // replaced from the current player's hand, otherwise false:
        // a tile can only be replaced if isReplaceLegal() is true
        bool replaceTile(Tile* tile); 
        
        // Used when loading game from file.
        void setTileBag (LinkedList* tileBag);

        // DELETE: FOR TESTING ONLY
        LinkedList* GetTileBag();

    private:

        // ** 2.3.2 The board **
        Board* board; 

        // ** 2.3.4 The tile bag **
        LinkedList* tileBag; 

        Player* player1;
        Player* player2;
        Player* currentPlayer;

        // Calculates the current player's score during
        // placeTile(), providing isPlaceLegal() is true
        ScoreCalculator* scoreCalculator;

        // Takes the tileBag pointer and fills it with 72 tiles,
        // in 6 colors and 6 shapes and 2 of each type
        void fillTileBag(LinkedList* tileBag);

        // Takes the tileBag pointer and shuffles the tiles inside
        // to create a random inital order for a new game
        void shuffleTileBag(LinkedList* tileBag);

        // Used after a player completes their turn to toggle
        // the currentPlayer between player1 and player2
        void nextPlayerTurn();

        // Take a tile pointer and returns true if replace 
        // is legal according to the rules, otherwise false: 
        // the tile must be in the current player’s hand  
        bool isReplaceLegal(Tile* tile) const;

        // Take a tile pointer, row (between A-Z) and 
        // col (between 0-25) and returns true if placement 
        // is legal according to the rules, otherwise false: 
        // (1) Tiles must share one colour or shape attribute 
        // (2) Tiles must be placed in the same line
        // (3) A line can never be longer than six tiles
        // (4) There cannot be duplicate tiles in a line
        // (5) You cannot play two tiles that are exactly the same
        // (6) The tile must be in the current player's hand
        bool isPlaceLegal(Tile* tile, char row, int col) const;
};

#endif // GAME_H