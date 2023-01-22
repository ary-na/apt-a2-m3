#include "../include/Controller.h"

Controller::Controller() {
    this->game = nullptr;
    this->validator = new Validator();
    this->fileHandler = new FileHandler();
    this->testFlag = false;
    this->exitMode = false;
}

Controller::Controller(const Controller& other) {   
    if (other.game != nullptr) {
        this->game = new Game(*other.game);
    } else {
        this->game = nullptr;
    }    
    this->validator = new Validator(*other.validator);
    this->fileHandler = new FileHandler(*other.fileHandler);
    this->testFlag = other.testFlag;
    this->exitMode = other.exitMode;
}

Controller::~Controller() {
    if (this->game != nullptr) {
        delete this->game;
        this->game = nullptr;
    }
    delete this->validator;
    this->validator = nullptr;
    delete this->fileHandler;
    this->fileHandler = nullptr;
}

void Controller::launchGame(bool testFlag) {

    // If the program was run in test  
    // mode, set the test flag to true.
    if(testFlag) {
        this->testFlag = testFlag;
    }

    // The program should display a welcome message.
    std::cout << std::endl;
    std::cout << "Welcome to Qwirkle" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << std::endl;

    // Then continue to the main menu.
    mainMenu();
}

void Controller::mainMenu() {
    do {
        // The main menu shows the options of the program.
        std::cout << "Menu" << std::endl;
        std::cout << "----" << std::endl;
        std::cout << std::endl;

        std::cout << "1. New game" << std::endl;
        std::cout << "2. Load game" << std::endl;
        std::cout << "3. Credits (show student information)" << std::endl;
        std::cout << "4. Quit" << std::endl;

        // The user selects an option by typing a number. 
        std::string menuInput = "";
        inputPrompt(&menuInput);

        if (menuInput == "1") {
            newGame();
        } else if (menuInput == "2") {
            loadGame();
        } else if (menuInput == "3") {
            credits();
        } else if (menuInput == "4") {
            exitGame();
        } else {
            std::cerr << "Select a valid menu option!" << std::endl;
            std::cout << std::endl;
        }
    } while (!this->isExitMode());
}

void Controller::newGame() {

    // Print a message for starting a new game.
    std::cout << "Starting a new game" << std::endl;
    std::cout << std::endl;

    // Ask for player 1 name.
    std::cout << "Enter a name for player 1 "
              << "(uppercase characters only)" << std::endl;

    std::string name1Input = "";
    playerNamePrompt(&name1Input);

    // Ask for player 2 name.
    std::cout << "Enter a name for player 2 "
              << "(uppercase characters only)" << std::endl;

    std::string name2Input = "";
    playerNamePrompt(&name2Input);

    // Create a new game of Qwirkle.
    Player *player1 = new Player(name1Input);
    Player *player2 = new Player(name2Input);
    this->game = new Game(player1, player2, this->testFlag);

    // Proceed with normal gameplay.
    std::cout << "Let's play!" << std::endl;
    std::cout << std::endl;
    baseGameplay();
}

void Controller::playerNamePrompt(std::string* nameInput) {
    bool awaitingInput = true;
    while (awaitingInput) {

        // Get player name input.
        inputPrompt(nameInput);

        // Players should only have letters, no numbers or symbols.
        bool nameValid = validator->isNameValid(*nameInput);

        if (!nameValid && !std::cin.eof()) {
            std::cerr << "Invalid input!" << std::endl;
            std::cout << std::endl;
        } else if (std::cin.eof()) {
            awaitingInput = false;
            exitGame();
        } else {
            awaitingInput = false;
        }
    }
}

void Controller::inputPrompt(std::string* input) {
    std::cout << "> ", getline(std::cin, *input);
    std::cout << std::endl;
}

void Controller::loadGame() {
    std::cout << "Load game" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << std::endl;

    // The program should ask the user for a file.
    std::cout << "Enter the filename from which load a game" << std::endl;

    bool awaitingInput = true;
    while (awaitingInput) { 

        // User enters the relative path to the saved game file.
        std::string fileName = "";
        inputPrompt(&fileName);

        // If the file passes validation checks, the game is loaded, 
        // a message is printed and normal fameplay continues.
        try {
            this->game = this->fileHandler->loadGame(fileName);
            awaitingInput = false;  

        // If the file doesn't pass the validation checks.
        } catch (std::out_of_range(& e)) {
            std::cerr << e.what() << std::endl;
            std::cout << std::endl;
            mainMenu();
        }
    }
    std::cout << "Qwirkle game successfully loaded" << std::endl;
    std::cout << std::endl;
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

    // The name of the current player.
    std::cout << this->game->getCurrentPlayer()->getName()
              << ", it's your turn" << std::endl;
    std::cout << std::endl;

    // The scores of both players.
    std::cout << "Score for " << this->game->getPlayer1()->getName() << ": "
              << this->game->getPlayer1()->getScore() << std::endl;

    std::cout << "Score for " << this->game->getPlayer2()->getName() << ": "
              << this->game->getPlayer2()->getScore() << std::endl;
    std::cout << std::endl;

    // The state of the board.
    this->game->getBoard()->printBoard();
    std::cout << std::endl;

    // The tiles in the current player’s hand.
    std::cout << "Your hand is" << std::endl;
    this->game->getCurrentPlayer()->getHand()->printList();
    std::cout << std::endl;

    // The user prompt.
    turnPrompt();
}

void Controller::turnPrompt() {
    bool awaitingInput = true;
    while (awaitingInput) {
        
        // Ask user to enter command.
        std::string commandInput = "";
        inputPrompt(&commandInput);
        int command = validator->isCommandValid(commandInput);

        // If command is invalid.
        if (command == -1) {
            std::cerr << "Invalid input!" << std::endl;
            std::cout << std::endl;

        // If command is place <colour><shape> at <row><col>.
        } else if (command == 1) {
            placeTile(commandInput, &awaitingInput);

        // If command is replace <colour><shape>.
        } else if (command == 2) {
            replaceTile(commandInput, &awaitingInput);

        // If command is save <filename>.
        } else if (command == 3) {
            saveGame(commandInput);

        // If command is EOF character ^D.
        } else if (command == 4) {
            awaitingInput = false;
            std::cout << std::endl;
            exitGame();
        }
    }
}

void Controller::placeTile(std::string commandInput, bool* inputStatus) {

    // Extract tile and from input.
    Colour colourInput = commandInput[6];
    Shape shapeInput = commandInput[7] - '0';
    Tile *tileInput = new Tile(colourInput, shapeInput);

    // Extract position from input.
    char rowInput = commandInput[12];
    int colInput;

    if (commandInput.length() > 14) {
        colInput = std::stoi(std::to_string(commandInput[13] - '0') + 
                   std::to_string(commandInput[14] - '0'));
    } else {
        colInput = commandInput[13] - '0';
    }

    // Try to place the tile.
    bool tilePlaced = this->game->placeTile(tileInput, rowInput, colInput);

    if (!tilePlaced) {
        std::cerr << "Illegal move!" << std::endl;
        std::cout << std::endl;
        delete tileInput;  
    } else {
        *inputStatus = false;
    }
}

void Controller::replaceTile(std::string commandInput, bool* inputStatus) {

    // Extract tile from input.
    Colour colourInput = commandInput[8];
    Shape shapeInput = commandInput[9] - '0';
    Tile *tileInput = new Tile(colourInput, shapeInput);

    // Try to replace the tile.
    bool tileReplaced = this->game->replaceTile(tileInput);
            
    if (!tileReplaced) {
        std::cerr << "Illegal move!" << std::endl;
        std::cout << std::endl;
        delete tileInput;
    } else {
        *inputStatus = false;
    }
}

void Controller::saveGame(std::string fileName) {

    this->fileHandler->saveGame(this->game, fileName);

    std::cout << "Game successfully saved" << std::endl;
    std::cout << std::endl;

}

void Controller::endGame() {

    // Display the end game message.
    std::cout << "Game over" << std::endl;
    std::cout << std::endl;

    // Display the scores.
    std::cout << "Score for " << this->game->getPlayer1()->getName() << ": "
              << this->game->getPlayer1()->getScore() << std::endl;

    std::cout << "Score for " << this->game->getPlayer2()->getName() << ": "
              << this->game->getPlayer2()->getScore() << std::endl;
    std::cout << std::endl;

    // Display the winner name.
    std::cout << "Player " << this->game->getHighestScorePlayer()
              << " won!" << std::endl;

    // Quit safely.
    exitGame();
}

bool Controller::isExitMode() const {
    return exitMode;
}

void Controller::setExitMode(bool exitMode) {
    Controller::exitMode = exitMode;
}