#include "../include/Controller.h"
#include <iostream>
#include <memory>

int main(void) {

    std::unique_ptr<Controller> controller(new Controller);
    // controller->launchGame();

    // Skip launchGame() to newGame() while menu unfinished
    controller->newGame();

    return EXIT_SUCCESS;
}