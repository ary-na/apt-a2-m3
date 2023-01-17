#include "../include/Controller.h"
#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {

    bool testFlag = false;

    if (argv[1] != nullptr)
    {
        if (*argv[1] == 'T')
        {
            testFlag = true;
        }
        
    }
    

    std::unique_ptr<Controller> controller(new Controller);
    controller->launchGame(testFlag);

    return EXIT_SUCCESS;
}