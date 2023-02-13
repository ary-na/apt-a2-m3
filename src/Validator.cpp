#include "../include/Validator.h"

Validator::Validator() {
    this->testFlag = false;
    this->aiFlag = false;
    this->multipleStatus = false;
}

Validator::Validator(const Validator &other) {
    this->testFlag = other.testFlag;
    this->aiFlag = other.aiFlag;
    this->multipleStatus = other.multipleStatus;
}

Validator::Validator(Validator &&other) : testFlag(other.testFlag), aiFlag(other.aiFlag), multipleStatus(other.multipleStatus) {
    other.testFlag = false;
    other.aiFlag = false;
    other.multipleStatus = false;
}

Validator::~Validator() = default;

void Validator::setTestFlag(const bool testFlag) {
    this->testFlag = testFlag;
}

void Validator::setAiFlag(const bool aiFlag) {
    this->aiFlag = aiFlag;
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

int Validator::isCommandValid(const std::string &command) const {
    int isValid = -1;

    // Check if place <colour><shape> at <row><col>
    if (std::regex_match(command, std::regex("place [R|O|Y|G|B|P][1-6] at [A-Z](0?[0-9]|1[0-9]|2[0-5])\\b")) &&
        !this->multipleStatus) {
        isValid = 1;
    }
    // Check if replace <colour><shape>
    else if (std::regex_match(command, std::regex("replace [R|O|Y|G|B|P][1-6]"))) {
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
    // Check if place multiple <colour><shape> at <row><col>
    else if (std::regex_match(command, std::regex("place multiple [R|O|Y|G|B|P][1-6] at [A-Z](0?[0-9]|1[0-9]|2[0-5])\\b")) && !this->aiFlag) {
        std::cout << "Add more tiles to the board" << std::endl;
        isValid = 7;
    }
    // Check if place multiple stop
    else if (std::regex_match(command, std::regex("stop place multiple")) && !this->aiFlag) {
        isValid = 8;
    }
    return isValid;
}

void Validator::setMultipleStatus(bool multipleStatus) {
    this->multipleStatus = multipleStatus;
}

