#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <iostream>
#include <fstream>
#include <regex>

class Validator {
public:

public:
    Validator();
    Validator(const Validator& other);
    Validator(Validator&& other);
    ~Validator();

    // Check if username is valid (Players should only consist of letters (no numbers or symbols))
    bool isNameValid(const std::string &input);

    // Check if saved file exist
    bool isSavedFileExist(std::string fileName);

    // bool isPlayerNameValid (std::string playerName);

    // Check if command input is valid
    int isCommandValid(const std::string &command);
};

#endif // VALIDATOR_H