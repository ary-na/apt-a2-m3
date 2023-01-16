#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "LinkedList.h"
#include "Game.h"
#include "Validator.h"
#include <iostream>
#include <string>
#include <sstream>

class FileHandler {
    public:
        FileHandler();
        ~FileHandler();
        
        // Loads the saved game file, will return a bool indicating 
        // if the game was loaded correctly. Will also print any errors 
        // to the console in any of the save files.
        bool loadGame(std::string fileName);
        
    private:
        // For validating user input 
        Validator* validator;

        // Absorb the load game file 
        // Assuming a valid file name is being passed to the function. 
        // Only the name needs to be passed not the path or extension. 
        bool absorbLoadGameFile(std::string fileName);

        // Generates the board with the current state of play.
        // Assuming a comma separated string is being passed to the function. 
        // Format being the tile data, followed by an “@” symbol, then the boards position.  
        // Example: “B4@B2, B6@B3, B5@B4”
        Board* boardFromFile (std::string boardState); 
        
        // Generate Hand from file.
        // Assuming a comma separated string is being passed to the 
        // function with tile data being represented as colour then shape 
        // Example “Y5,R5,O2”
        LinkedList* playerHandFromFile (std::string playerHandString);
        
        // Trim the start and end of a strign of whitespace
        std::string trim(const std::string & source);

        // Used to ensure a consistent error message
        void errorMessage(std::string);




};

#endif // FILEHANDLER_H