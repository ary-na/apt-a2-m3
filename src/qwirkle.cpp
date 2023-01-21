#include "../include/Controller.h"
#include <iostream>

int main(int argc, char* argv[]) {

    // When test flag is true, a random seed is set 
    // to ensure consistent randomness of the tile bag.
    // Run with "./qwirkle T" to activate test mode. 
    bool testFlag = false;
    if (argv[1] != nullptr) {
        if (*argv[1] == 'T') {
            testFlag = true;
        }
    }

    // Run Qwirkle program.
    Controller* controller(new Controller);
    controller->launchGame(testFlag);

    delete controller;
    controller = nullptr;

    return EXIT_SUCCESS;
}