#include "../include/Controller.h"

Controller::Controller() {
    this->game = nullptr;
    this->validator = new Validator();
    this->fileHandler = new FileHandler();
    this->exitMode = false;
}

Controller::~Controller() {
    if (this->game != nullptr) {
        delete this->game;
        this->game = nullptr;
    }
    delete this->validator;
    delete this->fileHandler;
    this->validator = nullptr;
}

void Controller::launchGame() {

    // The program should display a welcome message

    std::cout << std::endl;
    std::cout << "Welcome to Qwirkle" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << std::endl;

    // Then the program should continue to the main menu

    mainMenu();
}

void Controller::mainMenu() {

    do {
        std::cout << "Menu" << std::endl;
        std::cout << "----" << std::endl;
        std::cout << std::endl;
        std::cout << "1. New game" << std::endl;
        std::cout << "2. Load game" << std::endl;
        std::cout << "3. Credits (show student information)" << std::endl;
        std::cout << "4. Quit" << std::endl;

        // The user selects an option by typing a number, and pressing enter
        std::string menuInput;
        std::cout << "> ", getline(std::cin, menuInput);

        if (menuInput == "1")
            newGame();
        else if (menuInput == "2")
            loadGame();
        else if (menuInput == "3")
            credits();
        else if (menuInput == "4") {
            exitGame();
        } else {
            std::cerr << "Select a valid menu option!" << std::endl;
            std::cout << std::endl;
        }

    } while (!this->isExitMode());
}

void Controller::newGame() {

    // Print a message for starting a new game

    std::cout << std::endl;
    std::cout << "Starting a new game" << std::endl;
    std::cout << std::endl;

    // Ask for player 1 name

    std::cout << "Enter a name for player 1 "
              << "(uppercase characters only)" << std::endl;

    bool awaitingInput = true;
    std::string name1Input = "";

    while (awaitingInput) {
        std::cout << "> ", getline(std::cin, name1Input);
        std::cout << std::endl;

        // Players should only consist of letters (no numbers or symbols)

        // nameValid return true - If name is valid
        // nameValid return false - If name is inValid
        bool nameValid = validator->isNameValid(name1Input);

        if (!nameValid) {
            std::cout << "Invalid input!" << std::endl;
            std::cout << std::endl;
        } else {
            awaitingInput = false;
        }
    }

    // Ask for player 2 name

    std::cout << "Enter a name for player 2 "
              << "(uppercase characters only)" << std::endl;

    awaitingInput = true;
    std::string name2Input = "";

    while (awaitingInput) {
        std::cout << "> ", getline(std::cin, name2Input);
        std::cout << std::endl;

        // Players should only consist of letters (no numbers or symbols)

        // nameValid return true - If name is valid
        // nameValid return false - If name is inValid
        bool nameValid = validator->isNameValid(name2Input);

        if (!nameValid) {
            std::cout << "Invalid input!" << std::endl;
            std::cout << std::endl;
        } else {
            awaitingInput = false;
        }
    }

    // Create a new game of Qwirkle

    Player *player1 = new Player(name1Input);
    Player *player2 = new Player(name2Input);
    this->game = new Game(player1, player2);

    // Proceed with normal gameplay

    std::cout << "Let's play!" << std::endl;
    std::cout << std::endl;

    baseGameplay();
}

void Controller::loadGame() {

    // [JACOB] TODO
    std::cout << std::endl;
    std::cout << "Load game" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << std::endl;

    // The program should first ask the user for a 
    // filename from which to load a game

    std::cout << "Enter the filename from which load a game" << std::endl;
    std::cout << std::endl;

    // The user enters the relative path to 
    // the saved game file, and presses enter

    std::string fileName = "";
    std::cout << "> ", getline(std::cin, fileName);
    std::cout << std::endl;

    this->game = this->fileHandler->loadGame(fileName);
    baseGameplay();
}

void Controller::credits() {
    std::cout << std::endl;
    std::cout << "Credits" << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << std::endl;
    std::cout << "Name: Carelle Mulawa-Richards" << std::endl;
    std::cout << "Student ID: s3749114" << std::endl;
    std::cout << "Email: s3749114@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;
    std::cout << "Name: Jacob Depares" << std::endl;
    std::cout << "Student ID: S3851480" << std::endl;
    std::cout << "Email: S3851480@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;
    std::cout << "Name: Alexander Barron" << std::endl;
    std::cout << "Student ID: s3831619" << std::endl;
    std::cout << "Email: s3831619@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;
    std::cout << "Name: Arian Najafi Yamchelo" << std::endl;
    std::cout << "Student ID: S3910902" << std::endl;
    std::cout << "Email: S3910902@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;
}

void Controller::exitGame() {
    this->setExitMode(true);
    std::cout << std::endl;
    std::cout << "Goodbye" << std::endl;
    std::cout << std::endl;
}

void Controller::baseGameplay() {
    bool gameComplete = this->game->isComplete();
    while (!gameComplete && !this->isExitMode()) {
        takeTurn();
        gameComplete = this->game->isComplete();
    }

    if (!this->isExitMode())
        endGame();
}

void Controller::takeTurn() {

    // The name of the current player

    std::cout << this->game->getCurrentPlayer()->getName()
              << ", it's your turn" << std::endl;
    std::cout << std::endl;

    // The scores of both players

    std::cout << "Score for " << this->game->getPlayer1()->getName() << ": "
              << this->game->getPlayer1()->getScore() << std::endl;

    std::cout << "Score for " << this->game->getPlayer2()->getName() << ": "
              << this->game->getPlayer2()->getScore() << std::endl;
    std::cout << std::endl;

    // The state of the board

    this->game->getBoard()->printBoard();
    std::cout << std::endl;

    // The tiles in the current player’s hand

    std::cout << "Your hand is" << std::endl;
    this->game->getCurrentPlayer()->getHand()->printList();
    std::cout << std::endl;

    // The user prompt

    bool awaitingInput = true;

    while (awaitingInput) {

        std::string commandInput = "";
        std::cout << "> ", getline(std::cin, commandInput);
        std::cout << std::endl;

        int command = validator->isCommandValid(commandInput);

        // command return -1 - Invalid
        if (command == -1) {
            std::cout << "Invalid input!" << std::endl;
            std::cout << std::endl;

        }
        // command return 1 - place <colour><shape> at <row><col>
        else if (command == 1) {

            // Extract tile and position from input 

            Colour colourInput = commandInput[6];
            Shape shapeInput = commandInput[7] - '0';
            Tile *tileInput = new Tile(colourInput, shapeInput);
            char rowInput = commandInput[12];
            int colInput;

            if (commandInput.length() > 14) {
                colInput = std::stoi(std::to_string(commandInput[13] - '0') + 
                                     std::to_string(commandInput[14] - '0'));
            } else {
                colInput = commandInput[13] - '0';
            }

            // Try to place the tile

            bool tilePlaced = this->game->placeTile(tileInput, rowInput, colInput);

            if (!tilePlaced) {
                std::cout << "Illegal move!" << std::endl;
                std::cout << std::endl;
                delete tileInput;
            } else {
                awaitingInput = false;
            }

        }
        // command return 2 - replace <colour><shape>
        else if (command == 2) {

            // Extract tile from input

            Colour colourInput = commandInput[8];
            Shape shapeInput = commandInput[9] - '0';
            Tile *tileInput = new Tile(colourInput, shapeInput);

            // Try to replace the tile

            bool tileReplaced = this->game->replaceTile(tileInput);

            if (!tileReplaced) {
                std::cout << "Illegal move!" << std::endl;
                std::cout << std::endl;
                delete tileInput;
            } else {
                awaitingInput = false;
            }

        }
        // command return 3 - save <filename>
        else if (command == 3) {
            saveGame();

        }
        // command return 4 - ^D
        else if (command == 4) {
            awaitingInput = false;
            exitGame();
        }
    }
}

void Controller::saveGame() {

    // [JACOB] TODO

    // The program should save the current state of the game 
    // to the provided filename (overwriting the file if it already exists) 

    // Then the program should display a message 
    // and continue with the gameplay 

    std::cout << std::endl;
    std::cout << "Game successfully saved" << std::endl;
    std::cout << std::endl;

    // TO DO: Need to ask for the save game name

    this->fileHandler->saveGame("NewSaveGame");

    // The current player does not change, 
    // so that a player may save the game and then take a turn

    // If the program has problems saving the file, it should display 
    // a message, and continue with normal gameplay without crashing.
}

void Controller::endGame() {

    // Display the end game message, scores and winner name

    std::cout << "Game over" << std::endl;
    std::cout << std::endl;

    std::cout << "Score for " << this->game->getPlayer1()->getName() << ": "
              << this->game->getPlayer1()->getScore() << std::endl;

    std::cout << "Score for " << this->game->getPlayer2()->getName() << ": "
              << this->game->getPlayer2()->getScore() << std::endl;
    std::cout << std::endl;

    std::cout << "Player " << this->game->getHighestScorePlayer()
              << " won!" << std::endl;

    // Then quit, according to Section 2.2.4
    exitGame();
}

bool Controller::isExitMode() const {
    return exitMode;
}

void Controller::setExitMode(bool exitMode) {
    Controller::exitMode = exitMode;
}
