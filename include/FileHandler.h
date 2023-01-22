#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "LinkedList.h"
#include "Game.h"
#include "Board.h"
#include "Validator.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>

class FileHandler {
    public:
        FileHandler();
        FileHandler(const FileHandler& other);
        ~FileHandler();
        
        // @author - Jacob Depares
        // ** updates the current state of play based on a saved game file 
        // ** INPUT: Required a valid save file name. The path and extension of the game file is not required. 
        // ** OUTPUT: If the name of the file is valid, and the format of the file is valid, a Game* will be returned. 
        // If not, a NullPtr will be returned and an error will be printed out. 
        Game* loadGame(const std::string fileName);

        // @author - Jacob Depares
        // ** saves the current state of play to a “.save” file.
        // ** INPUT: The name of the file. If the file already exists, this will be overwritten. The name cannot contain special characters or whitespace. 
        // If it does the function will return false.
        //** OUTPUT: if the file is successfully saved, true will be returned, else an error will be printed and false will be returned.  
        bool saveGame(const Game* game, const std::string fileName);
        
    private:

        // @author - Jacob Depares
        // For validating user input 
        Validator* validator;

        // @author - Jacob Depares
        // ** returns players hand as a comma-separated string
        // ** INPUT: A linked list representing the players hand. 
        // ** OUTPUT: A comma-separated string representing the players hand with tile data being represented as colour than shape Example “Y5,R5,O2”.
        std::string playerHandToFile(const LinkedList* playerHand);

        // @author - Jacob Depares
        // ** returns board state as a comma-separated string
        // ** INPUT: the board in play 
        // ** OUTPUT: A comma-separated string with the format being the tile data, followed by an “@” symbol, then the board’s position. 
        // Example: “B4@B2, B6@B3, B5@B4”
        std::string boardStateToFile(const Board* board);

        // @author - Jacob Depares
        // ** returns tile bag as a comma-separated string
        // ** INPUT: A linked list representing the tile bag. 
        // ** OUTPUT: A comma-separated string representing the tile bag with tile data being represented as colour than shape Example “Y5,R5,O2”.
        std::string tileBagToFile(const LinkedList* tileBag);

        // @author - Jacob Depares
        // ** Absorbs the current game file and returns a Game* with the updated state of play.
        // ** INPUT: A valid save file name without the path or extension. It is assumed the file name is correct 
        // and the function is not accounting for incorrect file names. 
        // ** OUTPUT: if the format of the file is valid, a Game* will be returned. If not, a NullPtr will be returned and an error will be printed out.   
 
        Game* absorbLoadGameFile(const std::string fileName);
        
        // @author - Jacob Depares
        // ** Returns Hand from file.
        // ** INPUT: A comma-separated string is being passed to the function with tile data being represented as colour than shape Example “Y5,R5,O2”.
        // ** OUTPUT: A LinkedList* of tiles representing the current player’s hand. 
        LinkedList* playerHandFromFile (const std::string playerHandString);

        // @author - Jacob Depares
        // ** Updates the current state of the board for the game based on the state of play.   
        // ** INPUT: A comma-separated string with the format being the tile data, followed by an “@” symbol, then the board’s position. 
        // Example: “B4@B2, B6@B3, B5@B4”
        // ** Output: an initialised board with an updated board state
        Board* initaliseBoardFromFile (const std::string boardState);
        
        // @author - Jacob Depares
        // ** Returns Hand from file.
        // ** INPUT: A comma-separated string is being passed to the function with tile data being represented as colour than shape Example “Y5,R5,O2”.
        // ** OUTPUT: A LinkedList* of tiles representing the current player’s hand. 
        LinkedList* tileBagFromFile (const std::string playerHandString);   

        // @author - Jacob Depares
        // ** Returns the current player
        // ** INPUT: Valid current players and a player name
        // ** OUTPUT: if an invalid player name is passed, the function will return a NullPtr and produce an error. 
        // If a valid name is passed, the function will return a ptr to the player.
        Player* currentPlayerFromName (Player* P1, Player* P2, std::string playerName) const; 

        // @author - Jacob Depares
        // ** Trim the start and end of a strign of whitespace
        std::string trim(const std::string & source);
};

#endif // FILEHANDLER_H
