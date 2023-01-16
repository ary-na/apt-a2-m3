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
    std::cout << std::endl;
    std::cout << "Welcome to Qwirkle" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << std::endl;

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

    std::cout << std::endl;
    std::cout << "Starting a new game" << std::endl;
    std::cout << std::endl;

    // Ask for the player names

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

    std::string fileInput = "";
    std::cout << "> ", getline(std::cin, fileInput);
    std::cout << std::endl;
    fileInput = "savedGames/" + fileInput + ".txt";

    std::fstream infile;
    infile.open(fileInput);

    // Check if file exist 
    if(!infile.is_open()) {
        std::cout << "File does not exist" << std::endl;
        mainMenu();

    }

   
    
    // After the filename is provided, the program must then:

    // - Check that the file exists.


    // - Check that the format of the file is correct. 
    // The format for saved games is described in Section 2.3.7.

    // If the filename passes both checks, the program should print a message, 
    // then load the game as described in Section 2.3.12 
    //Absorb File 
   
    Player* player1;
    Player* player2;  
    int boardRows, boardCols;
    LinkedList* player1Hand = new LinkedList();
    LinkedList* player2Hand = new LinkedList();

    if(infile.is_open()){



        int x = 1;
        std::string line;
        while (getline(infile,line))
        {
            // Player 1 Name
            if (x == 1) {
                player1 = new Player(line);

            //Player 1 Score
            }else if(x == 2) {
                std::cout << player1->getScore() << std::endl;
                player1->addScore(std::stoi(line));
                std::cout << player1->getScore() << std::endl;

            }
            // Player 1 Hand
            else if (x == 3) {
                std::stringstream s_stream(line);
                while(s_stream.good()) {
                    std::string substr;
                    getline(s_stream, substr, ','); //get first string delimited by comma
                    std::string num(1 , substr[1]);
                    player1Hand->addEnd(new Tile(substr[0], std::stoi(num)));
                }

            // Player 2 Name
            }else if (x == 4) {
                player2 = new Player(line);

            // Player 2 Score
            } else if (x == 5) {
               player2->addScore(std::stoi(line));
            }
            // Player 2 Hand
            else if (x == 6) {
                std::stringstream s_stream(line);
                while(s_stream.good()) {
                    std::string substr;
                    getline(s_stream, substr, ','); //get first string delimited by comma
                    std::string num(1 , substr[1]);
                    player2Hand->addEnd(new Tile(substr[0], std::stoi(num)));
                }
            }

            // Board Size 
            else if (x == 7) {

                // We are currently not absorbing the board size dynamically due to assignment spec. 
                // Reading in for enhencments. 
                std::stringstream s_stream(line);

                bool rowComplete = false;
                while(s_stream.good()) {
                    std::string substr;
                    getline(s_stream, substr, ','); //get first string delimited by comma

                    if(!rowComplete) {
                        boardRows =  std::stoi(substr);
                        rowComplete = true;

                    } else {
                        boardCols = std::stoi(substr);
                    }
                 
                }

                // All details to create the board are present,
                // Create the board now as we will need an initialised 
                // board when we load the state on the next line
                this->game = new Game(player1, player2);

                    std::cout << this->game->getPlayer1()->getScore() << std::endl;
    std::cout << this->game->getPlayer2()->getScore() << std::endl;

                player1 = nullptr;
                player2 = nullptr;

            // Board state
            } else if (x == 8) {
                std::stringstream s_stream(line);
                while(s_stream.good()) {
                    std::string substr;
                    getline(s_stream, substr, ','); //get first string delimited by comma   
                    substr = trim(substr);
                   /* std::cout << substr << std::endl;
                    std::cout << substr[0] << std::endl;
                    
                    std::cout << std::stoi(num) << std::endl;
                    std::cout << substr[3] << std::endl;
                    std::cout << stoi(substr.substr(substr.find('@') + 2, substr.length())) << std::endl;*/
                    std::string num(1 , substr[1]);
                    this->game->placeTile(new Tile(substr[0],std::stoi(num)), substr[3], 
                                stoi(substr.substr(substr.find('@') + 2, substr.length())));


                    //std::string col(1 , substr);
                    
                }

            // Tile Bag
            }  else if (x == 9) {
                
                LinkedList* tileBag = new LinkedList();
                std::stringstream s_stream(line);
                while(s_stream.good()) {
                    std::string substr;
                    getline(s_stream, substr, ','); //get first string delimited by comma
                    std::string num(1 , substr[1]);
                    tileBag->addEnd(new Tile(substr[0], std::stoi(num)));
                }

                this->game->setTileBag(tileBag);
                tileBag = nullptr;

            // Current Player
            } else if (x == 10) {
                this->game->getPlayer1()->getName().compare(line) ? this->game->setCurrentPlayer(this->game->getPlayer1()) :
                            this->game->setCurrentPlayer(this->game->getPlayer2());
                
            }



            ++x;            
        }
        
        infile.close();

    } 

    // Creating the new game

    

    /* Updating the game
    this->game->getPlayer1()->addScore(player1Score);
    this->game->getPlayer2()->addScore(player2Score);

    this->game->getPlayer1()->setHand(player1Hand);
    this->game->getPlayer2()->setHand(player2Hand);
*/
    //std::cout << this->game->getPlayer1()->getName() << std::endl;
    //std::cout << this->game->getPlayer2()->getName() << std::endl;

    
    //std::cout << this->game->getBoard()->getBoardRows() << std::endl;
    //std::cout << this->game->getBoard()->getBoardCols() << std::endl;

    std::cout << this->game->getPlayer1()->getScore() << std::endl;
    std::cout << this->game->getPlayer2()->getScore() << std::endl;

   // this->game->getPlayer1()->getHand()->printList();
   // this->game->getPlayer2()->getHand()->printList();
   // this->game->GetTileBag()->printList();

   // std::cout << this->game->getCurrentPlayer()->getName() << std::endl;

    // Delete

    player1Hand = nullptr;
    player2Hand = nullptr;

    std::cout << "Qwirkle game successfully loaded" << std::endl;

    // and continue with normal gameplay as described in Section 2.3.

    //baseGameplay();
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
    std::cout << "Student ID: s3851480" << std::endl;
    std::cout << "Email: s3851480@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;

    std::cout << "Name: Alexander Barron" << std::endl;
    std::cout << "Student ID: s3831619" << std::endl;
    std::cout << "Email: s3831619@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;

    std::cout << "Name: Arian Najafi Yamchelo" << std::endl;
    std::cout << "Student ID: S3910902" << std::endl;
    std::cout << "Email: S3910902@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;

    // After printing the student details, 
    // the program should return to the main menu
}

void Controller::exitGame() {
    std::cout << std::endl;
    std::cout << "Goodbye" << std::endl;
    std::cout << std::endl;
}

void Controller::baseGameplay() {
    bool gameComplete = this->game->isComplete();
    while (!gameComplete) {
        takeTurn();
        gameComplete = this->game->isComplete();
    }
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
                std::string colStr = std::to_string(commandInput[13] - '0') +
                                     std::to_string(commandInput[14] - '0');
                colInput = std::stoi(colStr);
            }

            Tile *tileInput = new Tile(colourInput, shapeInput);

            bool tilePlaced = this->game->placeTile(tileInput, rowInput, colInput);
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

            bool tileReplaced = this->game->replaceTile(tileInput);
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
    
    std::cout << std::endl;
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
              << this->game->getPlayer1()->getName() << ": "
              << this->game->getPlayer1()->getScore() << std::endl;

    std::cout << "Score for "
              << this->game->getPlayer2()->getName() << ": "
              << this->game->getPlayer2()->getScore() << std::endl;

    std::cout << std::endl;

    // Display the name of the winning player

    std::cout << "Player " << this->game->getHighestScorePlayer()
              << " won!" << std::endl;

    // Then quit, according to Section 2.2.4

    exitGame();
}

// Misc Functions
std::string Controller::trim(const std::string & source) {
    std::string s(source);
    s.erase(0,s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t")+1);
    return s;
}