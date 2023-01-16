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
        
    private:
        // For validating user input 
        Validator* validator;

        // Absorb the load game file 
        bool absorbLoadGameFile(std::string fileName);

        std::string trim(const std::string & source);
};

#endif // FILEHANDLER_H