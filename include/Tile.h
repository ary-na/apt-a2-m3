#ifndef TILE_H
#define TILE_H

#include "TileCodes.h"

typedef char Colour; 
typedef int Shape; 

class Tile {
    public:
     
        // Delete default constructor to 
        // enforce parameterised constructor 
        Tile() = delete;

        // Constructor for making a tile: 
        // takes a colour and shape (see TileCodes.h)
        Tile(Colour colour, Shape shape);

        // Deep copy constructor 
        Tile(const Tile& other);

        // Destructor 
        ~Tile();

        Colour colour;
        Shape shape;
        
    private:
};

#endif // TILE_H