#ifndef PLAYER_H
#define PLAYER_H

#include "Hand.h"
#include <string>
#include <iostream>
#include <utility>

// @author - Carelle Mulawa-Richards

class Player {
public:
    // Constructor for adding a new player.
    explicit Player(const std::string& name, bool computer = false);

    // Constructor for loading a player.
    Player(const std::string& name, int score, Hand *hand, bool computer = false);

    Player(const Player &other);

    Player(Player &&other);

    ~Player();

    // Returns the player's name.
    std::string getName() const;

    // Returns the player's score.
    int getScore() const;

    // Returns the player's hand.
    Hand *getHand() const;

    // Takes a number >= 0 and adds it to the score.
    void addScore(int score);

    // Computer AI getter
    bool isComputer() const;

private:
    std::string name;
    int score;
    Hand *hand;
    bool computer;
};

#endif // PLAYER_H