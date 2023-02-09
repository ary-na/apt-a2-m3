#include "../include/Computer.h"

Computer::Computer(Player *player) {
    this->player = player;
    this->hand = player->getHand();
    this->handTiles = player->getHand()->getHandList();
    this->targetRow = 0;
    this->targetCol = 0;
    this->tileColour = 0;
    this->tileShape = 0;
    this->targetScore = 0;
}

Computer::Computer(const Computer &other) {
    this->player = other.player;
    this->hand = other.hand;
    this->handTiles = other.handTiles;
    this->targetRow = other.targetRow;
    this->targetCol = other.targetCol;
    this->tileColour = other.tileColour;
    this->tileShape = other.tileShape;
    this->targetScore = other.targetScore;
}

Computer::Computer(Computer &&other) :
        player(other.player),
        hand(other.hand),
        handTiles(other.handTiles),
        targetRow(other.targetRow),
        targetCol(other.targetCol),
        tileColour(other.tileColour),
        tileShape(other.tileShape),
        targetScore(other.targetScore) {
    other.player = nullptr;
    other.hand = nullptr;
    other.handTiles = nullptr;
    other.targetRow = 0;
    other.targetCol = 0;
    other.tileColour = 0;
    other.tileShape = 0;
    other.targetScore = 0;
}

Computer::~Computer() {
    this->player = nullptr;
    this->hand = nullptr;
    this->handTiles = nullptr;
}

void Computer::printMove() {
    std::cout << "PC hand is" << std::endl;
    this->hand->printHand();
    std::cout << std::endl;
    std::cout << "PC placed " << getTileColour() << getTileShape() << " at " << getTargetRow() << getTargetCol()
              << std::endl;
    std::cout << std::endl;
}

char Computer::getTargetRow() const {
    return this->targetRow;
}

int Computer::getTargetCol() const {
    return this->targetCol;
}

Colour Computer::getTileColour() const {
    return this->tileColour;
}

Shape Computer::getTileShape() const {
    return this->tileShape;
}

int Computer::getTargetScore() const {
    return targetScore;
}

void Computer::setTargetRow(char targetRow) {
    Computer::targetRow = targetRow;
}

void Computer::setTargetCol(int targetCol) {
    Computer::targetCol = targetCol;
}

void Computer::setTileColour(Colour tileColour) {
    Computer::tileColour = tileColour;
}

void Computer::setTileShape(Shape tileShape) {
    Computer::tileShape = tileShape;
}

void Computer::setTargetScore(int targetScore) {
    Computer::targetScore = targetScore;
}

Hand *Computer::getHand() const {
    return hand;
}

LinkedList *Computer::getHandTiles() const {
    return handTiles;
}