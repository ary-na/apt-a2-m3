#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "LinkedList.h"
#include "Game.h"
#include "Validator.h"
#include "FileHandler.h"
#include "Hand.h"
#include <iostream>
#include <string>
#include <sstream>

class Controller {
    public:
        Controller();
        Controller(const Controller& other);
        Controller(Controller&& other);
        ~Controller();

        // Used by main() to start the program. Displays a 
        // welcome message and continues to the main menu. 
        void launchGame(bool testFlag); 

private:
        Game* game;
        Validator* validator;
        FileHandler* fileHandler;

        // If exit mode is true, the mainMenu() loop 
        // will end and the game will exit safely.  
        bool exitMode;

        // When test flag is true, a random seed is set when the 
        // game shuffles the tiles to ensure consistent randomness. 
        // Run with "./qwirkle T" to activate test mode.
        bool testFlag;

        // Displays the main menu and asks the user 
        // to make a selection by typing a number. 
        void mainMenu();

        // Asks for the names and makes a new game. 
        void newGame(); 

        // Used in newGame(). Assigns name input to given string pointer.
        void playerNamePrompt(std::string* nameInput, 
                              const std::string &nameInput1 = "");

        // Asks the user for a relative path to a saved game file. 
        // If file is valid, the game is loaded and gameplay continues. 
        // Otherwise, the user is taken back to the main menu.
        void loadGame(); 

        // Displays details of each student in the group.
        void credits(); 

        // Displays a goodbye message and quits safely. 
        void exitGame();

        // During baseGameplay(), players will takeTurn() placing tiles 
        // from their hand onto the board, until the game is complete.
        void baseGameplay();
        void takeTurn();

        // Tries to skip the current player's turn,
        // the input status is set to true if successful.
        void skipTurn(bool* inputStatus);

        // Takes a player and displays their score. 
        void playerScore(Player* player);

        // Called during takeTurn(). Asks the user to 
        // enter a command, validates it and processes it.
        // (1) <colour><shape> at <row><col>
        // (2) replace <colour><shape>
        // (3) save <filename>
        // (4) EOF character ^D
        // (5) skip
        void turnPrompt();

        // Takes the user command and tries to place a tile, 
        // the input status is set to true if successful.
        void placeTile(std::string commandInput, bool* inputStatus);

        // Takes the user command and tries to replace a tile, 
        // the input status is set to true if successful.
        void replaceTile(std::string commandInput, bool* inputStatus);

        // Displays the end game message, scores, 
        // winner name and safely quits the program. 
        void endGame(); 

        // Takes the user command and tries and tries to save the 
        // current game. If sucessfully saved, gameplay continues.
        void saveGame(const std::string fileName);

        // Promts the user to enter an input and
        // assigns it to the given string pointer.
        void inputPrompt(std::string* input); 

        // Returns true if game is in exist mode. 
        bool isExitMode() const;

        // Sets the exit mode to true or false. 
        void setExitMode(bool exitMode);
};

#endif // CONTROLLER_H