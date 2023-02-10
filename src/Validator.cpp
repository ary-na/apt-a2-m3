#include "../include/Validator.h"

Validator::Validator() {
    this->testFlag = false;
}

Validator::Validator(const Validator &other) {
    this->testFlag = other.testFlag;
}

Validator::Validator(Validator &&other) : testFlag(other.testFlag) {
    other.testFlag = false;
}

Validator::~Validator() {
}

void Validator::setTestFlag(const bool testFlag) {
    this->testFlag = testFlag;
}

bool Validator::isNameValid(const std::string &nameInput, const std::string &nameInput1) {

    // This function should be called with a string parameter.
    // It will return a boolean value depending on the string input.
    // This is a public function and can be called from the controller
    // to validate username input.

    bool nameValid = true;

    // Check if name input matches the regex, and nameInput1 is empty
    if (std::regex_match(nameInput, std::regex("[A-Z]+")) && nameInput1.empty()) {
        nameValid = false;
    }
    // Check if name input matches the regex,
    // and players don't have the same name
    else if (std::regex_match(nameInput, std::regex("[A-Z]+")) && nameInput != nameInput1) {
        nameValid = false;
    }

    return nameValid;
}

bool Validator::isSavedFileExist(std::string fileName) {

    std::string path = this->testFlag ? "tests/" + fileName + ".save" :
                       "savedGames/" + fileName + ".save";

    std::fstream infile;
    infile.open(path);

    bool validPath = true;
    // Check if file exist 
    if (!infile.is_open()) {
        validPath = false;
    }

    infile.close();
    return validPath;
}

int Validator::isCommandValid(const std::string &command) {
    int isValid = -1;

    // Check if place <colour><shape> at <row><col>
    if (std::regex_match(command, std::regex(
            "place [R|O|Y|G|B|P][1-6] at [A-Z](0?[0-9]|1[0-9]|2[0-5])\\b"))) {
        isValid = 1;
    }
    // Check if replace <colour><shape>
    else if (std::regex_match(command,
                              std::regex("replace [R|O|Y|G|B|P][1-6]"))) {
        isValid = 2;
    }
    // Check if save <filename>
    else if (std::regex_match(command, std::regex("save [A-Za-z1-9]+"))) {
        isValid = 3;
    }
    // Check if ^D (EOF)
    else if (std::cin.eof()) {
        isValid = 4;
    }
    // Check if skip
    else if (std::regex_match(command, std::regex("skip"))) {
        isValid = 5;
    }
    // Check if help
    else if (std::regex_match(command, std::regex("help"))) {
        isValid = 6;
    }

    return isValid;
}

