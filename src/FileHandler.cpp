#include "../include/FileHandler.h"

FileHandler::FileHandler() {
    this->validator = new Validator();
}

FileHandler::~FileHandler() {
    delete this->validator;
    this->validator = nullptr;
}

bool FileHandler::loadGame(std::string fileName) {

    // Validates the file exist
    if(!this->validator->isSavedFileExist(fileName)){
        errorMessage("File does not exist!");
        return false;
    } else {
        absorbLoadGameFile(fileName);
    }
    
    return true;
}

bool FileHandler::absorbLoadGameFile(std::string fileName) {

    std::string path = "savedGames/" + fileName + ".save";
    std::fstream infile;
    infile.open(path);

    // Save the content to a vector allowing the game to be created cleanly.
    std::vector<std::string> fileContent;
    
     if(infile.is_open()) {        
        std::string line;
        while (getline(infile,line)) 
            fileContent.push_back(line);
    }


    Player* P1 = new Player(fileContent[0],std::stoi(fileContent[1]),playerHandFromFile(fileContent[2]));
    Player* P2 = new Player(fileContent[3],std::stoi(fileContent[4]),playerHandFromFile(fileContent[5]));

    boardFromFile (fileContent[7]);
    
    std::cout << P1->getName() << std::endl;  
    std::cout << P1->getScore() << std::endl;  
    P1->getHand()->printList();

    std::cout << P2->getName() << std::endl;  
    std::cout << P2->getScore() << std::endl;  
    P2->getHand()->printList();
    
    infile.close();
    return true;
}

Board* FileHandler:: boardFromFile (std::string boardState) {
    std::stringstream s_stream(boardState);
        while(s_stream.good()) {
            std::string substr;
            getline(s_stream, substr, ',');
            substr = trim(substr);

            std::cout << substr << std::endl;

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

std::string FileHandler::trim(const std::string & source) {
    std::string s(source);
    s.erase(0,s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t")+1);
    return s;
}

void FileHandler::errorMessage(std::string error) {
    std::cout << "ERROR: " << error << std::endl;
}