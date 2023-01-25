#ifndef TILE_H
#define TILE_H

#include "TileCodes.h"
#include <iostream>
#include <utility>

typedef char Colour; 
typedef int Shape; 

class Tile {
    public:
        // Constructor for making a tile. Takes a colour 
        // and shape, see TileCodes.h for more info.
        Tile(Colour colour, Shape shape);

        Tile(const Tile& other);
        Tile(Tile&& other);
        ~Tile();

        // Returns the tile colour and shape as a string. 
        std::string getAsString();

        Colour colour;
        Shape shape;
        
    private:
};

#endif // TILE_H