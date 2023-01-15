#include "../include/Player.h"

Player::Player(std::string name) {
    this->name = name;
    this->score = 0;
    this->hand = new LinkedList();
}

Player::Player(const Player& other) {
    this->name = other.name;
    this->score = other.score;
    this->hand = new LinkedList(*other.hand);
}

Player::~Player() {
    delete this->hand;
    this->hand = nullptr;
}

std::string Player::getName() const {
    return this->name;
}

int Player::getScore() const {
    return this->score;
}

LinkedList* Player::getHand() const {
    
    return this->hand;
}

void Player::setHand(LinkedList* hand) {
    this->hand = hand;
}

void Player::addScore(int score) {
    this->score = this->score + score;
}