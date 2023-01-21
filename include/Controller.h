#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "LinkedList.h"
#include "Game.h"
#include "Validator.h"
#include "FileHandler.h"
#include <iostream>
#include <string>
#include <sstream>

class Controller {
    public:
        Controller();
        Controller(const Controller& other);
        ~Controller();

        // Used by main() to start the program. Displays a 
        // welcome message and continues to the main menu. 
        void launchGame(bool testFlag); 

private:
        Game* game;
        Validator* validator;
        FileHandler* fileHandler;
        bool exitMode;

        // When test flag is true, a random seed is set during when 
        // the game shuffles the tiles to ensure consistent randomness. 
        // Run with "./qwirkle T" to activate test mode.
        bool testFlag;

        // ** 2.2 Main menu **
        void mainMenu();

        // ** 2.2.1 New game **
        // ** 2.3.10 Special operation: Starting a new game **
        void newGame(); 

        // Helper function for newGame(). Takes a player 
        // name pointer and assigns user input to it.
        void playerNamePrompt(std::string* nameInput);

        // ** 2.2.2 Load game **
        // ** 2.3.12 Special operation: loading a game **
        void loadGame(); 

        // Displays the name, student number, and 
        // email address of each student in the group.
        void credits(); 

        // Displays a goodbye message and quits safely. 
        void exitGame();

        // ** 2.3 Base Gameplay **
        void baseGameplay();
        void takeTurn();

        // Helper function for takeTurn(). Asks the user to 
        // enter a command, validates it and processes it.
        void turnPrompt();

        // Helper function for turnPromt(). Takes the user command and tries 
        // tp place a tile, the input status is set to true if successful.
        void placeTile(std::string commandInput, bool* inputStatus);

        // Helper function for turnPromt(). Takes the user command and tries  
        // to replace a tile, the input status is set to true if successful.
        void replaceTile(std::string commandInput, bool* inputStatus);

        // Displays the end game message, scores, 
        // winner name and safely quits the program. 
        void endGame(); 

        // ** 2.3.7 Function: Saving the Game **
        void saveGame(std::string fileName);

        // Returns true if game is in exist mode. 
        bool isExitMode() const;

        // Sets the exit mode to true or false. 
        void setExitMode(bool exitMode);

        // Absorb the load game file 
        bool absorbLoadGameFile(std::string fileName);
        
        // Promts the user to enter an input and
        // assigns it to the given string pointer.
        void inputPrompt(std::string* input);   
};

#endif // CONTROLLER_H