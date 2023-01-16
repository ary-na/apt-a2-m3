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

    ~Validator();

    // Check if username is valid (Players should only consist of letters (no numbers or symbols))
    bool isNameValid(const std::string &input);

    // Check if saved file exist
    bool isSavedFileExist(std::string fileName);

    // bool isPlayerNameValid (std::string playerName);

};

#endif // VALIDATOR_H