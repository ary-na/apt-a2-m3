#include "../include/Controller.h"
#include <iostream>

int main(void) {

    Controller* controller = new Controller();
    controller->launchGame();

    delete controller;
    controller = nullptr;

    return EXIT_SUCCESS;
}