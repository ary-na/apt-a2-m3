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

        // Default constructor 
        Controller();

        // TODO: Deep copy constructor

        // Destructor
        ~Controller();

        // ** 2.1 Launch **
        void launchGame(); 

private:
        Game* game;
        Validator* validator;
        FileHandler* fileHandler;
        bool exitMode;

        // ** 2.2 Main menu **
        void mainMenu();

        // ** 2.2.1 New game **
        // ** 2.3.10 Special operation: Starting a new game **
        void newGame(); 

        // Helper function for newGame():
        // Takes a string pointer for a player 
        // name and assigns user input to it
        void playerNamePrompt(std::string* nameInput);

        // ** 2.2.2 Load game **
        // ** 2.3.12 Special operation: loading a game **
        void loadGame(); 

        // ** 2.2.3 Credits **
        void credits(); 

        // ** 2.2.4 Quit **
        // ** 2.3.8 Function: Quit **
        void exitGame();

        // ** 2.3 Base Gameplay **
        void baseGameplay();
        void takeTurn();
        void turnPrompt();

        // ** 2.3.11 Special operation: ending a game **
        void endGame(); 

        // ** 2.3.7 Function: Saving the Game **
        void saveGame();

        // ExitMode getter
        bool isExitMode() const;

        // ExitMode setter
        void setExitMode(bool exitMode);

        // Absorb the load game file 
        bool absorbLoadGameFile(std::string fileName);    

        void inputPrompt(std::string* input);   
};

#endif // CONTROLLER_H