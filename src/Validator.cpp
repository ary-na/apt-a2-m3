#include "../include/Validator.h"
#include <regex>

Validator::Validator() {
}

Validator::~Validator() {

}

bool Validator::isNameValid(const std::string &input) {
    return std::regex_match(input, std::regex("[A-Z]+"));
}
