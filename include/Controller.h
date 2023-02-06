#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "LinkedList.h"
#include "Game.h"
#include "Validator.h"
#include "FileHandler.h"
#include "Hand.h"
#include <iostream>
#include <string>
#include <sstream>

// @author - Carelle Mulawa-Richards (unless specified)

class Controller {
public:
    Controller();

    Controller(const Controller &other);

    Controller(Controller &&other);

    ~Controller();

    // Used by main() to start the program. Displays a
    // welcome message and continues to the main menu.
    void launchGame(bool testFlag, bool aiFlag);

private:
    Game *game;

    // @author - Arian Najafi Yamchelo
    Validator *validator;

    // @author - Jacob Depares
    FileHandler *fileHandler;

    // @author - Arian Najafi Yamchelo
    // If exit mode is true, the mainMenu() loop
    // will end and the game will exit safely.
    bool exitMode;

    // @author - Alex Barron
    // When test flag is true, a random seed is set when the
    // game shuffles the tiles to ensure consistent randomness.
    // Run with "./qwirkle T" to activate test mode.
    bool testFlag;

    // @author - Arian Najafi Yamchelo
    // When AI flag is true, you can play against computer.
    // Run with "./qwirkle --ai" to activate AI mode.
    bool aiFlag;

    // @author - Arian Najafi Yamchelo
    // Displays the main menu and asks the user
    // to make a selection by typing a number.
    void mainMenu();

    // Asks for the player names and makes a new game.
    void newGame();


    // Used in newGame(). Assigns name input to given string pointer.
    void playerNamePrompt(std::string *nameInput,
                          const std::string &nameInput1 = "");

    // @author - Jacob Depares
    // Asks the user for a relative path to a saved game file.
    // If file is valid, the game is loaded and gameplay continues.
    // Otherwise, the user is taken back to the main menu.
    void loadGame();

    // Displays details of each student in the group.
    static void credits();

    // @author - Arian Najafi Yamchelo
    // Displays a goodbye message and quits safely.
    void exitGame();

    // During baseGameplay(), players will takeTurn() placing tiles
    // from their hand onto the board, until the game is complete.
    void baseGameplay();

    void takeTurn();

    // @author - Alex Barron
    // Tries to skip the current player's turn,
    // the input status is set to true if successful.
    void skipTurn(bool *inputStatus);

    // Takes a player and displays their score.
    static void playerScore(Player *player);

    // @author - Arian Najafi Yamchelo
    // Called during takeTurn(). Asks the user to
    // enter a command, validates it and processes it.
    // (1) <colour><shape> at <row><col>
    // (2) replace <colour><shape>
    // (3) save <filename>
    // (4) EOF character ^D
    // (5) skip
    void turnPrompt();

    // Takes the user command and tries to place a tile,
    // the input status is set to true if successful.
    void placeTile(std::string commandInput, bool *inputStatus);

    // Takes the user command and tries to replace a tile,
    // the input status is set to true if successful.
    void replaceTile(std::string commandInput, bool *inputStatus);

    // @author - Arian Najafi Yamchelo
    // Displays the end game message, scores,
    // winner name and safely quits the program.
    void endGame();

    // @author - Jacob Depares
    // Takes the user command and tries and tries to save the
    // current game. If sucessfully saved, gameplay continues.
    void saveGame(const std::string fileName);

    // Promts the user to enter an input and
    // assigns it to the given string pointer.
    static void inputPrompt(std::string *input);

    // @author - Arian Najafi Yamchelo
    // Returns true if game is in exist mode.
    bool isExitMode() const;

    // @author - Arian Najafi Yamchelo
    // Sets the exit mode to true or false.
    void setExitMode(bool exitMode);
};

#endif // CONTROLLER_H