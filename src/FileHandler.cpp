#include "../include/FileHandler.h"

FileHandler::FileHandler() {
    this->validator = new Validator();
}

FileHandler::~FileHandler() {
    delete this->validator;
    this->validator = nullptr;
}

Game* FileHandler::loadGame(std::string fileName) {

    // Validates the file exist
    if(!this->validator->isSavedFileExist(fileName)){
        errorMessage("File does not exist!");
        return nullptr;
    }
    
    return absorbLoadGameFile(fileName);
}

bool FileHandler::saveGame(std::string fileName) {

    return true;
}

Game* FileHandler::absorbLoadGameFile(std::string fileName) {

    std::string path = "savedGames/" + fileName + ".save";
    std::fstream infile;
    infile.open(path);

    // Save the content of the file to a vector allowing the game to be created cleanly.
    std::vector<std::string> fileContent;
    if(infile.is_open()) {        
        std::string line;
        while (getline(infile,line)) 
            fileContent.push_back(line);
    }

    infile.close();

    // Create players
    Player* P1 = new Player(fileContent[0],std::stoi(fileContent[1]),playerHandFromFile(fileContent[2]));
    Player* P2 = new Player(fileContent[3],std::stoi(fileContent[4]),playerHandFromFile(fileContent[5]));

    // Create Game
    Game* game = new Game(P1, P2, new Board(), tileBagFromFile(fileContent[8]),currentPlayerFromName(P1, P2, fileContent[9]));
 
    // Update board state
    boardStateFromFile (game, fileContent[7]);

    // Clean up
    P1 = nullptr;
    P2 = nullptr;

    return game;
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

void FileHandler:: boardStateFromFile (Game* game, std::string boardState) {
    std::stringstream s_stream(boardState);
        while(s_stream.good()) {
            std::string substr;
            getline(s_stream, substr, ',');
            substr = trim(substr);

            std::string num(1 , substr[1]);
            game->getBoard()->addTileAtPos(new Tile(substr[0],std::stoi(num)), substr[3], 
                    stoi(substr.substr(substr.find('@') + 2, substr.length())));

        }
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

void FileHandler::errorMessage(std::string error) {
    std::cout << "ERROR: " << error << std::endl;
}
