#ifndef PLAYER_H
#define PLAYER_H

#include "LinkedList.h"
#include <string>
#include <iostream>

class Player {
    public:
        // Constructor for adding a new player
        Player(std::string name);

        // Constructor for loading a player
        Player(std::string name, int score, LinkedList* hand);

        // Copy constructor 
        Player(const Player& other);

        // Destructor 
        ~Player();

        // Returns the player's name
        std::string getName() const;

        // Returns the player's score
        int getScore() const;

        // Returns a pointer to the player's hand
        LinkedList* getHand() const;

        // Sets the hand, is used when we load a hand from a saved game
        void setHand(LinkedList*);

        // Takes a number >= 0 and adds it to player score
        void addScore(int score);

    private:
        std::string name;
        int score;

        // ** 2.3.3 The player’s hand **
        LinkedList* hand; 
};

#endif // PLAYER_H