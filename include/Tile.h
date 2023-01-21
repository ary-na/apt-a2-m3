#ifndef TILE_H
#define TILE_H

#include "TileCodes.h"

typedef char Colour; 
typedef int Shape; 

class Tile {
    public:
        // Constructor for making a tile. Takes a colour 
        // and shape, see TileCodes.h for more info.
        Tile(Colour colour, Shape shape);

        Tile(const Tile& other);
        ~Tile();

        Colour colour;
        Shape shape;
        
    private:
};

#endif // TILE_H