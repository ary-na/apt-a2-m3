#include "../include/FileHandler.h"

FileHandler::FileHandler() {
    this->validator = new Validator();
    this->testFlag = false;
    this->aiFlag = false;
}

FileHandler::FileHandler(const FileHandler& other) {
    this->validator = new Validator(*other.validator);
    this->testFlag = other.testFlag;
    this->aiFlag = other.aiFlag;
}

FileHandler::FileHandler(FileHandler&& other) {
    this->validator = other.validator;
    this->testFlag = other.testFlag;
    this->aiFlag = other.aiFlag;
    other.testFlag = false;
    other.aiFlag = false;
}

FileHandler::~FileHandler() {
    delete this->validator;
    this->validator = nullptr;
}

void FileHandler::setTestFlag(const bool testFlag) {
    this->testFlag = testFlag;
    this->validator->setTestFlag(testFlag);
}

void FileHandler::setAiFlag(const bool aiFlag) {
    this->aiFlag = aiFlag;
}

bool FileHandler::saveGame(const Game* game, const std::string fileName) {

    std::string path = this->testFlag ? "tests/" + fileName.substr(5, fileName.length()) + ".save" :
                       "savedGames/" + fileName.substr(5, fileName.length()) + ".save";

    std::fstream outFile;

    this->validator->isSavedFileExist(fileName) ?
    outFile.open(path, std::ios::app) :
    outFile.open(path, std::ios::out);

    if (outFile.is_open()) {
        outFile << game->getPlayer1()->getName() << std::endl;
        outFile << game->getPlayer1()->getScore() << std::endl;
        outFile << playerHandToFile(game->getPlayer1()->getHand()) << std::endl;
        outFile << game->getPlayer2()->getName() << std::endl;
        outFile << game->getPlayer2()->getScore() << std::endl;
        outFile << playerHandToFile(game->getPlayer2()->getHand()) << std::endl;
        outFile << std::to_string(game->getBoard()->getMaxRow() + 1) + "," +
                   std::to_string(game->getBoard()->getMaxCol() + 1) << std::endl;
        outFile << boardStateToFile(game->getBoard()) << std::endl;
        outFile << tileBagToFile(game->getTileBag()) << std::endl;
        outFile << game->getCurrentPlayer()->getName() << std::endl;
        outFile << game->getPlayer2()->isComputer();

        outFile.close();
    }

    // Validates the fileCreate successfully
    if (!this->validator->isSavedFileExist(fileName.substr(5, fileName.length()))) {
        throw std::invalid_argument("Game did not save correctly!");
    }

    return true;
}

std::string FileHandler::playerHandToFile(Hand* playerHand) {
    return playerHand->getAsStr();
}

std::string FileHandler::boardStateToFile(Board* board) {
    return board->getAsStr();
}

std::string FileHandler::tileBagToFile(TileBag* tileBag) {
    return tileBag->getAsStr();
}

Game* FileHandler::loadGame(const std::string fileName) {

    // Validates the file exist
    if (!this->validator->isSavedFileExist(fileName)) {
        throw std::out_of_range("File does not exist!");
    }
    return absorbLoadGameFile(fileName);
}

Game* FileHandler::absorbLoadGameFile(const std::string fileName) {

    std::string path = this->testFlag ? "tests/" + fileName + ".save" :
                       "savedGames/" + fileName + ".save";

    std::fstream inFile;
    inFile.open(path);

    // Save the content of the file to a vector allowing the game to be created cleanly.
    std::vector<std::string> fileContent;
    if (inFile.is_open()) {
        std::string line;
        while (getline(inFile,line)) {
            fileContent.push_back(line);
        }
    }

    inFile.close();

    // Load game with players, board and tile bag from file.
    Player* player1 = new Player(fileContent[0], std::stoi(fileContent[1]), playerHandFromFile(fileContent[2]));
    Player* player2 = new Player(fileContent[3], std::stoi(fileContent[4]), playerHandFromFile(fileContent[5]), std::stoi(fileContent[10]));
    Player* currentPlayer = currentPlayerFromName(player1, player2, fileContent[9]);
    Board* board = initialiseBoardFromFile(fileContent[7]);
    TileBag* tileBag = tileBagFromFile(fileContent[8]);

    Game* game = new Game();
    bool loaded = game->loadGame(player1, player2, board, tileBag, currentPlayer);

    // If unsuccessful, cleanup and show error.
    if (!loaded) {
        delete player1;
        player1 = nullptr;
        delete player2;
        player2 = nullptr;
        delete board;
        board = nullptr;
        delete tileBag;
        tileBag = nullptr;
        delete game;
        game = nullptr;
        throw std::logic_error("File has incorrect tiles!");

        // If successful, cleanup pointers and return game.
    } else {
        player1 = nullptr;
        player2 = nullptr;
        currentPlayer = nullptr;
        board = nullptr;
        tileBag = nullptr;
    }
    return game;
}

Hand* FileHandler::playerHandFromFile(const std::string playerHandString) {
    Hand* playerHand = new Hand();

    if (playerHandString != "") {
        std::stringstream s_stream(playerHandString);
        while (s_stream.good()) {
            std::string substr;
            getline(s_stream, substr, ',');
            std::string num(1, substr[1]);
            playerHand->addTile(new Tile(substr[0], std::stoi(num)));
        }
    }
    return playerHand;
}

Board* FileHandler:: initialiseBoardFromFile (const std::string boardState) {
    Board* board = new Board ();

    if (boardState != "") {
        std::stringstream s_stream(boardState);
        while (s_stream.good()) {
            std::string substr;
            getline(s_stream, substr, ',');
            substr = trim(substr);

            std::string num(1, substr[1]);

            board->addTileAtPos(new Tile(substr[0],std::stoi(num)), substr[3],
                                stoi(substr.substr(substr.find('@') + 2, substr.length())));
        }
    }
    return board;
}

TileBag* FileHandler::tileBagFromFile(const std::string tileBagString) {
    TileBag* tileBag = new TileBag();

    if (tileBagString != "") {
        std::stringstream s_stream(tileBagString);
        while (s_stream.good()) {
            std::string substr;
            getline(s_stream, substr, ',');
            std::string num(1 , substr[1]);
            tileBag->addTile(new Tile(substr[0], std::stoi(num)));
        }
    }
    return tileBag;
}

Player* FileHandler::currentPlayerFromName(Player* player1, Player* player2,
                                           std::string playerName) const {
    return  player1->getName().compare(playerName) == 0 ? player1 : player2;
}

std::string FileHandler::trim(const std::string & source) {
    std::string s(source);
    s.erase(0, s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t") + 1);
    return s;
}