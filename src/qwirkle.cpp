// COSC2136: Advanced Programming Techniques 
// Assignment 2: Implementing Qwirkle
// Milestone 3: Qwirkle Implementation (Individual Component)

// Prepared by Group 2:
// @author - Carelle Mulawa-Richards (s3749114)
// @author - Jacob Depares (s3851480)
// @author - Alexander Barron (s3831619)
// @author - Arian Najafi Yamchelo (s3910902)

#include "../include/Controller.h"
#include <iostream>

int main(int argc, char *argv[]) {

    // When test flag is true, a random seed is set 
    // to ensure consistent randomness of the tile bag.
    // Run with "./qwirkle T" to activate test mode. 
    bool testFlag = false;

    // When AI flag is true, you can play against computer.
    // Run with "./qwirkle --ai" to activate AI mode.
    bool aiFlag = false;

    if (argv[1] != nullptr) {
        if (*argv[1] == 'T') {
            testFlag = true;
        } else if (strcmp(argv[1], "--ai") == 0) {
            aiFlag = true;
        } else if (strcmp(argv[1], "--aiTest") == 0) {
            testFlag = true;
            aiFlag = true;
        }
    }

    // Run Qwirkle program.
    Controller *controller(new Controller);
    controller->launchGame(testFlag, aiFlag);

    delete controller;
    controller = nullptr;

    return EXIT_SUCCESS;
}