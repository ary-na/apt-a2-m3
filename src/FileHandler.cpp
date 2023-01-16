#include "../include/FileHandler.h"

FileHandler::FileHandler() {
    this->validator = new Validator();
}

FileHandler::~FileHandler() {
    delete this->validator;
    this->validator = nullptr;
}



bool FileHandler::absorbLoadGameFile(std::string fileName) {

    std::string path = "savedGames/" + fileName + ".txt";
    
    std::fstream infile;
    infile.open(path);

    

    // Check if file exist 
    if(infile.is_open()) {
        int fileLine = 1;
        std::string line;
        while (getline(infile,line)) {

            if(fileLine == 1) {
                if(this->validator->isPlayerNameValid(line)){


                } else {
                    return false;
                }


            }


        
        

    
    
            ++fileLine; 
        }   
    }
    
    infile.close();
    return true;
}

// Misc Functions
std::string FileHandler::trim(const std::string & source) {
    std::string s(source);
    s.erase(0,s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t")+1);
    return s;
}