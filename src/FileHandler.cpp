#include "../include/FileHandler.h"

FileHandler::FileHandler() {
    this->validator = new Validator();
}

FileHandler::FileHandler(const FileHandler& other) {
    // DON'T DELETE, WE NEED TO DO THIS FOR EVERY CLASS
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

bool FileHandler::saveGame (Game* game, std::string fileName) {
    

    std::string path = "savedGames/" + fileName.substr(5, fileName.length()) + ".save";
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

    return true;
}

std::string FileHandler::playerHandToFile(LinkedList* playerHand) {

    std::string stringPlayerHand = "";
    for(int x = 1; x < playerHand->getLength() + 1; x++) {
        std::string tile = playerHand->getAtPos(x)->colour + std::to_string(playerHand->getAtPos(x)->shape);
        x == 1 ? stringPlayerHand = tile : stringPlayerHand.append("," + tile);
    }

    return stringPlayerHand;
}

std::string FileHandler::boardStateToFile(Board* board) {

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

std::string FileHandler::tileBagToFile(LinkedList* tileBag) {

    std::string stringTileBag = "";
    for(int x = 1; x < tileBag->getLength() + 1; x++) {
        std::string tile = tileBag->getAtPos(x)->colour + std::to_string(tileBag->getAtPos(x)->shape);
        x == 1 ? stringTileBag = tile : stringTileBag.append("," + tile);
    }

    return stringTileBag;
}

Game* FileHandler::loadGame( std::string fileName) {

    // Validates the file exist
    if(!this->validator->isSavedFileExist(fileName)){
        // errorMessage("File does not exist!");
        throw std::out_of_range("File does not exist!");
    }
    return absorbLoadGameFile(fileName);
}

Game* FileHandler::absorbLoadGameFile(std::string fileName) {

    std::string path = "savedGames/" + fileName + ".save";
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

    try {
        // Create players
        Player* P1 = new Player(fileContent[0],std::stoi(fileContent[1]),playerHandFromFile(fileContent[2]));
        Player* P2 = new Player(fileContent[3],std::stoi(fileContent[4]),playerHandFromFile(fileContent[5]));

        // Create Game    
        Game* game = new Game(P1, P2, initaliseBoardFromFile (fileContent[7]), tileBagFromFile(fileContent[8]),currentPlayerFromName(P1, P2, fileContent[9]));

       // Clean up
        P1 = nullptr;
        P2 = nullptr;

        return game;

    } catch (std::out_of_range(& e)) {
        throw std::out_of_range(e.what());
        
        // Clean up
        return nullptr;
    }
}

LinkedList* FileHandler::playerHandFromFile (std::string playerHandString){
    LinkedList* playerHand = new LinkedList();
    std::stringstream s_stream(playerHandString);
    while(s_stream.good()) {
        std::string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        std::string num(1 , substr[1]);
        playerHand->addEnd(new Tile(substr[0], std::stoi(num)));
    }
    return playerHand;
}

Board* FileHandler:: initaliseBoardFromFile (std::string boardState) {
    Board* board = new Board ();
    std::stringstream s_stream(boardState);
        while(s_stream.good()) {
            std::string substr;
            getline(s_stream, substr, ',');
            substr = trim(substr);

            std::string num(1 , substr[1]);

            board->addTileAtPos(new Tile(substr[0],std::stoi(num)), substr[3], 
                    stoi(substr.substr(substr.find('@') + 2, substr.length())));

        }

        return board;
}

LinkedList* FileHandler::tileBagFromFile (std::string tileBagString){
    LinkedList* tileBag = new LinkedList();
    std::stringstream s_stream(tileBagString);
    while(s_stream.good()) {
        std::string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        std::string num(1 , substr[1]);
        tileBag->addEnd(new Tile(substr[0], std::stoi(num)));
    }
    return tileBag;
}

Player* FileHandler::currentPlayerFromName (Player* P1, Player* P2, std::string playerName){
    return  P1->getName().compare(playerName) == 1 ? P1 : P2;
}

std::string FileHandler::trim(const std::string & source) {
    std::string s(source);
    s.erase(0,s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t")+1);
    return s;
}