#include "../include/Controller.h"
#include <iostream>
#include <memory>

int main(void) {

    std::unique_ptr<Controller> controller(new Controller);
    controller->launchGame();

    return EXIT_SUCCESS;
}