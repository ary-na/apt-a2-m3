#include "../include/Player.h"

Player::Player(const std::string& name, bool computer) {
    this->name = name;
    this->score = 0;
    this->hand = new Hand();
    this->computer = computer;
}

Player::Player(const std::string& name, int score, Hand *hand, bool computer) {
    this->name = name;
    this->score = score;
    this->hand = hand;
    this->computer = computer;
}

Player::Player(const Player &other) {
    this->name = other.name;
    this->score = other.score;
    this->hand = new Hand(*other.hand);
    this->computer = other.computer;
}

Player::Player(Player &&other) {
    this->name = other.name;
    this->score = other.score;
    this->hand = other.hand;
    this->computer = other.computer;
    other.name = "";
    other.score = 0;
    other.hand = nullptr;
    other.computer = false;
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

Hand *Player::getHand() const {
    return this->hand;
}

void Player::addScore(int score) {
    this->score = this->score + score;
}

bool Player::isComputer() const {
    return computer;
}