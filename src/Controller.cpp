#include "../include/Controller.h"

Controller::Controller() {
    this->game = nullptr;
    this->validator = new Validator();
}

Controller::~Controller() {
    if (this->game != nullptr) {
        delete this->game;
        this->game = nullptr;
    }
    delete this->validator;
    this->validator = nullptr;
}

void Controller::launchGame() {

    // On launch, the program should display a welcome message

    std::cout << "Welcome to Qwirkle" << std::endl;
    std::cout << "------------------" << std::endl;

    // Then the program should continue to the main menu
    mainMenu();
}

void Controller::mainMenu() {

    bool exit = false;

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
        std::cout << std::endl;

        if (menuInput == "1")
            newGame();
        else if (menuInput == "2")
            loadGame();
        else if (menuInput == "3")
            credits();
        else if (menuInput == "4") {
            exit = true;
            exitGame();
        } else {
            std::cerr << "Select a valid menu option!" << std::endl;
            std::cout << std::endl;
        }
    } while (!exit);
}

void Controller::newGame() {

    // Print a message for starting a new game

    std::cout << "Starting a new game" << std::endl;
    std::cout << std::endl;

    // Ask for the player names

    std::cout << "Enter a name for player 1 "
              << "(uppercase characters only)" << std::endl;

    bool awaitingInput = true;
    std::string name1Input;

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

    std::cout << "Enter a name for player 2 "
              << "(uppercase characters only)" << std::endl;

    awaitingInput = true;
    std::string name2Input;

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

    std::cout << "Load game" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << std::endl;

    // The program should first ask the user for a 
    // filename from which to load a game

    std::cout << "Enter the filename from which load a game" << std::endl;
    std::cout << std::endl;

    // The user enters the relative path to 
    // the saved game file, and presses enter

    std::string fileInput = "";
    std::cout << "> ", getline(std::cin, fileInput);
    std::cout << std::endl;

    // After the filename is provided, the program must then:

    // - Check that the file exists.

    // - Check that the format of the file is correct. 
    // The format for saved games is described in Section 2.3.7.

    // If the filename passes both checks, the program should print a message, 
    // then load the game as described in Section 2.3.12 

    std::cout << "Qwirkle game successfully loaded" << std::endl;

    // and continue with normal gameplay as described in Section 2.3.

    baseGameplay();
}

void Controller::credits() {
    std::cout << "Credits" << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << std::endl;

    std::cout << "Name: Carelle Mulawa-Richards" << std::endl;
    std::cout << "Student ID: s3749114" << std::endl;
    std::cout << "Email: s3749114@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;

    // [EVERYONE] TODO: Student 2 information
    std::cout << "Name: " << std::endl;
    std::cout << "Student ID: " << std::endl;
    std::cout << "Email: @student.rmit.edu.au" << std::endl;
    std::cout << std::endl;

    // [EVERYONE] TODO: Student 3 information
    std::cout << "Name: " << std::endl;
    std::cout << "Student ID: " << std::endl;
    std::cout << "Email: @student.rmit.edu.au" << std::endl;
    std::cout << std::endl;

    // [EVERYONE] TODO: Student 4 information
    std::cout << "Name: Arian Najafi Yamchelo" << std::endl;
    std::cout << "Student ID: S3910902" << std::endl;
    std::cout << "Email: S3910902@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;

    // After printing the student details, 
    // the program should return to the main menu
}

void Controller::exitGame() {
    std::cout << "Goodbye" << std::endl;
    std::cout << std::endl;
}

void Controller::baseGameplay() {
    bool gameComplete = game->isComplete();
    while (!gameComplete) {
        takeTurn();
        gameComplete = game->isComplete();
    }
    endGame();
}

void Controller::takeTurn() {

    // The name of the current player

    std::cout << game->getCurrentPlayer()->getName()
              << ", it's your turn" << std::endl;
    std::cout << std::endl;

    // The scores of both players

    std::cout << "Score for " << game->getPlayer1()->getName() << ": "
              << game->getPlayer1()->getScore() << std::endl;

    std::cout << "Score for " << game->getPlayer2()->getName() << ": "
              << game->getPlayer2()->getScore() << std::endl;
    std::cout << std::endl;

    // The state of the board

    game->getBoard()->printBoard();
    std::cout << std::endl;

    // The tiles in the current player’s hand

    std::cout << "Your hand is" << std::endl;
    game->getCurrentPlayer()->getHand()->printList();
    std::cout << std::endl;

    // The user prompt

    bool awaitingInput = true;

    while (awaitingInput) {

        std::string commandInput = "";
        std::cout << "> ", getline(std::cin, commandInput);
        std::cout << std::endl;

        // [ARIAN] TODO: Check that the command is correctly formatted

        // int command  = validate.command(commandInput);

        // command return 1 - place <colour><shape> at <row><col>
        // command return 2 - replace <colour><shape>
        // command return 3 - save <filename>
        // command return 4 - ^D
        // command return -1 - Invalid

        int command = 1;

        if (command == -1) {
            std::cout << "Invalid input!" << std::endl;
            std::cout << std::endl;

        } else if (command == 1) {

            // Extract Tile and postition from input 

            Colour colourInput = commandInput[6];
            Shape shapeInput = commandInput[7] - '0';
            char rowInput = commandInput[12];
            int colInput = commandInput[13] - '0';

            if (commandInput.length() > 14) {
                std::string colStr = std::to_string(commandInput[13]) +
                                     std::to_string(commandInput[14]);
                colInput = std::stoi(colStr);
            }

            Tile *tileInput = new Tile(colourInput, shapeInput);

            bool tilePlaced = game->placeTile(tileInput, rowInput, colInput);
            // tilePlaced return true - If tile successfully placed
            // tilePlaced return false - If illegal move

            if (!tilePlaced) {
                std::cout << "Illegal move!" << std::endl;
                std::cout << std::endl;
                delete tileInput;
            } else {
                awaitingInput = false;
            }

        } else if (command == 2) {

            // Extract tile from input

            Colour colourInput = commandInput[8];
            Shape shapeInput = commandInput[9] - '0';
            Tile *tileInput = new Tile(colourInput, shapeInput);

            bool tileReplaced = game->replaceTile(tileInput);
            // tileReplaced return true - If tile successfully replaced
            // tileReplaced return false - If illegal move

            if (!tileReplaced) {
                std::cout << "Illegal move!" << std::endl;
                std::cout << std::endl;
                delete tileInput;
            } else {
                awaitingInput = false;
            }

        } else if (command == 3) {
            saveGame();

        } else if (command == 4) {
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

    std::cout << "Game successfully saved" << std::endl;
    std::cout << std::endl;

    // The current player does not change, 
    // so that a player may save the game and then take a turn

    // If the program has problems saving the file, it should display 
    // a message, and continue with normal gameplay without crashing.
}

void Controller::endGame() {

    // Display the end game message

    std::cout << "Game over" << std::endl;
    std::cout << std::endl;

    // Display the scores

    std::cout << "Score for "
              << game->getPlayer1()->getName() << ": "
              << game->getPlayer1()->getScore() << std::endl;

    std::cout << "Score for "
              << game->getPlayer2()->getName() << ": "
              << game->getPlayer2()->getScore() << std::endl;

    std::cout << std::endl;

    // Display the name of the winning player

    std::cout << "Player " << game->getHighestScorePlayer()
              << " won!" << std::endl;

    // Then quit, according to Section 2.2.4

    exitGame();
}