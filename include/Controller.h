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
        ~Controller();

        // ** 2.1 Launch **
        void launchGame(); 

        // ** 2.2 Main menu **
        void mainMenu(); 

        // ** 2.2.1 New game **
        void newGame(); 

        // ** 2.2.2 Load game **
        // ** 2.3.12 Special operation: loading a game **
        void loadGame(); 

        // ** 2.2.3 Credits **
        void credits(); 

        // ** 2.2.4 Quit **
        // ** 2.3.8 Function: Quit **
        static void exitGame();

        // ** 2.3 Base Gameplay **
        void baseGameplay(); 
        void takeTurn();

        // ** 2.3.11 Special operation: ending a game **
        void endGame(); 

        // ** 2.3.7 Function: Saving the Game **
        void saveGame(); 
        
    private:
        Game* game;

        // For validating user input 
        Validator* validator;

        FileHandler* fileHandler;

        // Absorb the load game file 
        bool absorbLoadGameFile(std::string fileName);
};

#endif // CONTROLLER_H