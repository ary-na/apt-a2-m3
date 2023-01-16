#include "../include/Validator.h"

Validator::Validator() {
}

Validator::~Validator() {
}

bool Validator::isNameValid(const std::string &input) {

    // @author - Arian Najafi Yamchelo
    // This function should be called with a string parameter.
    // It will return a boolean value depending on the string input.
    // This is a public function and can be called from the controller to validate username input.

    return std::regex_match(input, std::regex("[A-Z]+"));
}

bool Validator::isSavedFileExist(std::string fileName) {
    std::string path = "savedGames/" + fileName + ".save";

    std::fstream infile;
    infile.open(path);

    // Check if file exist 
    if (!infile.is_open()) {
        return false;

    }

    infile.close();
    return true;
}

