#include "../include/Validator.h"

Validator::Validator() {
}

Validator::Validator(const Validator& other) {
    // [ARIAN] TODO
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

int Validator::isCommandValid(const std::string &command) {
    int isValid = -1;

    // Check if place <colour><shape> at <row><col>
    if (std::regex_match(command, std::regex("place [R|O|Y|G|B|P][1-6] at [A-Z](0?[0-9]|1[0-9]|2[0-5])\\b")))
        isValid = 1;
    // Check if replace <colour><shape>
    else if (std::regex_match(command, std::regex("replace [R|O|Y|G|B|P][1-6]")))
        isValid = 2;
    // Check if save <filename>
    else if (std::regex_match(command, std::regex("save [A-Za-z1-9]+")))
        isValid = 3;
    // Check if ^D (EOF)
    else if(std::cin.eof())
        isValid = 4;

    return isValid;
}

