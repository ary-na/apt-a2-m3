#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <iostream>
#include <fstream>
#include <regex>

// @author - Arian Najafi Yamchelo

class Validator {

    public:

        Validator();

        Validator(const Validator &other);

        Validator(Validator &&other);

        ~Validator();

        // Check if username is valid
        // (Players should only consist of letters (no numbers or symbols))
        bool isNameValid(const std::string &input, const std::string &nameInput1);

        // Check if saved file exist
        bool isSavedFileExist(std::string fileName);

        // Check if command input is valid
        int isCommandValid(const std::string &command);

        void setTestFlag(const bool testFlag);

    private:

        // When test flag is true, a random seed is set when the 
        // game shuffles the tiles to ensure consistent randomness. 
        // Run with "./qwirkle T" to activate test mode.
        bool testFlag;
    };

#endif // VALIDATOR_H