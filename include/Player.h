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
        Player(std::string name);

        // Constructor for loading a player.
        Player(std::string name, int score, Hand* hand);

        Player(const Player& other);
        Player(Player&& other);
        ~Player();

        // Returns the player's name.
        std::string getName() const;

        // Returns the player's score.
        int getScore() const;

        // Returns the player's hand.
        Hand* getHand() const;

        // Takes a number >= 0 and adds it to the score.
        void addScore(int score);

    private:
        std::string name;
        int score;
        Hand* hand;
};

#endif // PLAYER_H