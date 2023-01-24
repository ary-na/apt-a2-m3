#include "../include/FileHandler.h"

FileHandler::FileHandler() {
    this->validator = new Validator();
    this->testFlag = false;
}

FileHandler::FileHandler(const FileHandler& other) {
    this->validator = new Validator(*other.validator);
}

// FileHandler::FileHandler(FileHandler&& other) {
//     // [JACOB] TODO
//     // DON'T DELETE, WE NEED TO DO THIS FOR EVERY CLASS
// }

FileHandler::~FileHandler() {
    delete this->validator;
    this->validator = nullptr;
}

void FileHandler::setTestFlag(const bool testFlag){
    this->testFlag = testFlag;
    this->validator->setTestFlag(testFlag);
}

bool FileHandler::saveGame(const Game* game, const std::string fileName) {
    
    std::string path = this->testFlag ? "tests/" + fileName.substr(5, fileName.length()) + ".save": 
            "savedGames/" + fileName.substr(5, fileName.length()) + ".save";
    
    std::fstream outFile;

    this->validator->isSavedFileExist(fileName) ?
        outFile.open(path, std::ios::app) :
            outFile.open(path, std::ios::out);

    if(outFile.is_open()){
        outFile << game->getPlayer1()->getName() << std::endl;
        outFile << game->getPlayer1()->getScore() << std::endl;
        outFile << playerHandToFile(game->getPlayer1()->getHand()) << std::endl;
        outFile << game->getPlayer2()->getName() << std::endl;
        outFile << game->getPlayer2()->getScore() << std::endl;
        outFile << playerHandToFile(game->getPlayer2()->getHand()) << std::endl;
        outFile << std::to_string(game->getBoard()->getMaxRow()) + "," + 
                   std::to_string(game->getBoard()->getMaxCol()) << std::endl;
        outFile << boardStateToFile(game->getBoard()) << std::endl;
        outFile << tileBagToFile(game->getTileBag()) << std::endl;
        outFile << game->getCurrentPlayer()->getName();

        outFile.close();
    }
    
    // Validates the fileCreate successfully
    if(!this->validator->isSavedFileExist(fileName.substr(5, fileName.length()))){
        throw std::invalid_argument("Game did not save correctly!");
    }

    return true;
}

std::string FileHandler::playerHandToFile(const LinkedList* playerHand) {

    std::string stringPlayerHand = "";
    for(int x = 1; x < playerHand->getLength() + 1; x++) {
        std::string tile = playerHand->getAtPos(x)->colour + std::to_string(playerHand->getAtPos(x)->shape);
        x == 1 ? stringPlayerHand = tile : stringPlayerHand.append("," + tile);
    }
    
    return stringPlayerHand;
}

std::string FileHandler::boardStateToFile(const Board* board) {

    std::string boardState = "";

      for (char row = 'A'; toupper(row) - 'A' <= board->getMaxRow(); row++) {
        for (int col = 0; col <= board->getMaxCol() ; col++) {   
            Tile* tile = board->getTileAtPos(row, col);
            if(tile !=  nullptr) {
                std::string tileString = tile->colour + std::to_string(tile->shape) + "@" + row + std::to_string(col);
                boardState == "" ? boardState = tileString : boardState = boardState + " ," + tileString;
            }
        }
    }

    return boardState;
}

std::string FileHandler::tileBagToFile(const TileBag* tileBag) {

    std::string stringTileBag = "";
    for(int x = 1; x < tileBag->getNumOfTiles() + 1; x++) {
        std::string tile = tileBag->getTileList()->getAtPos(x)->colour + std::to_string(tileBag->getTileList()->getAtPos(x)->shape);
        x == 1 ? stringTileBag = tile : stringTileBag.append("," + tile);
    }

    return stringTileBag;
}

Game* FileHandler::loadGame(const std::string fileName) {

    // Validates the file exist
    if(!this->validator->isSavedFileExist(fileName)){
        throw std::out_of_range("File does not exist!");
    }
    return absorbLoadGameFile(fileName);
}

Game* FileHandler::absorbLoadGameFile(const std::string fileName) {

    std::string path = this->testFlag ? "tests/" + fileName + ".save": 
        "savedGames/" + fileName + ".save";

    std::fstream inFile;
    inFile.open(path);

    // Save the content of the file to a vector allowing the game to be created cleanly.
    std::vector<std::string> fileContent;
    if(inFile.is_open()) {        
        std::string line;
        while (getline(inFile,line)) 
            fileContent.push_back(line);
    }

    inFile.close();

    // Load game with players, board and tile bag from file.
    Player* player1 = nullptr;
    Player* player2 = nullptr;
    Player* currentPlayer = nullptr;
    Board* board = nullptr;
    TileBag* tileBag = nullptr;
    Game* game = new Game();
    
    try {
        player1 = new Player(fileContent[0], std::stoi(fileContent[1]), playerHandFromFile(fileContent[2]));
        player2 = new Player(fileContent[3], std::stoi(fileContent[4]), playerHandFromFile(fileContent[5]));
        currentPlayer = currentPlayerFromName(player1, player2, fileContent[9]);                 
        board = initaliseBoardFromFile(fileContent[7]);
        tileBag = tileBagFromFile(fileContent[8]);
        game->loadGameData(player1, player2, board, tileBag, currentPlayer);

    // If game cannot be loaded from file.
    } catch (std::invalid_argument(& e)) {
        throw std::invalid_argument(e.what());
    }

    // Clean up.
    player1 = nullptr;
    player2 = nullptr;
    currentPlayer = nullptr;
    board = nullptr;
    tileBag = nullptr;

    return game;
}

LinkedList* FileHandler::playerHandFromFile (const std::string playerHandString){
    LinkedList* playerHand = new LinkedList();
    
    if(playerHandString != "") {
        std::stringstream s_stream(playerHandString);
        while(s_stream.good()) {
            std::string substr;
            getline(s_stream, substr, ','); //get first string delimited by comma
            std::string num(1 , substr[1]);
            playerHand->addEnd(new Tile(substr[0], std::stoi(num)));
        }
    }
    return playerHand;
}

Board* FileHandler:: initaliseBoardFromFile (const std::string boardState) {
    Board* board = new Board ();

    if(boardState != "") {
        std::stringstream s_stream(boardState);
            while(s_stream.good()) {
                std::string substr;
                getline(s_stream, substr, ',');
                substr = trim(substr);

                std::string num(1 , substr[1]);

                board->addTileAtPos(new Tile(substr[0],std::stoi(num)), substr[3], 
                        stoi(substr.substr(substr.find('@') + 2, substr.length())));

            }
        }
    
    return board;
}

TileBag* FileHandler::tileBagFromFile(const std::string tileBagString){
    TileBag* tileBag = new TileBag();

    if(tileBagString != "") {
        std::stringstream s_stream(tileBagString);
        while(s_stream.good()) {
            std::string substr;
            getline(s_stream, substr, ','); //get first string delimited by comma
            std::string num(1 , substr[1]);
            tileBag->addTile(new Tile(substr[0], std::stoi(num)));
        }
    }
    return tileBag;
}

Player* FileHandler::currentPlayerFromName (Player* P1, Player* P2, std::string playerName) const{
    return  P1->getName().compare(playerName) == 1 ? P1 : P2;
}

std::string FileHandler::trim(const std::string & source) {
    std::string s(source);
    s.erase(0,s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t")+1);
    return s;
}