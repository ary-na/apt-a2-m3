#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

class Validator {

public:
    Validator();

    ~Validator();

    // Validate username input (Players should only consist of letters (no numbers or symbols))
    bool isNameValid(const std::string& input);

private:

};

#endif // VALIDATOR_H