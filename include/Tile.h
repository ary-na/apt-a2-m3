#ifndef TILE_H
#define TILE_H

#include "TileCodes.h"
#include <iostream>
#include <utility>

// @author - Carelle Mulawa-Richards

typedef char Colour;
typedef int Shape;

class Tile {
public:
    // Constructor for making a tile. Takes a colour
    // and shape, see TileCodes.h for more info.
    Tile(Colour colour, Shape shape);

    Tile(const Tile &other);

    Tile(Tile &&other);

    ~Tile();

    // Returns the tile colour and shape as a string.
    std::string getAsStr();

    // @author - Arian Najafi Yamchelo
    // Returns the tile colour as colour and shape as unicode/string.
    std::string getAsUnicodeAndColour();

    Colour colour;
    Shape shape;

private:

    // @author - Arian Najafi Yamchelo
    // Returns the tile colour as colour. Takes tile shape as unicode/string,
    // concatenates both and returns it.
    std::string getColourAsColour(const std::string& unicode) const;

    // @author - Arian Najafi Yamchelo
    // Returns the tile shape as unicode/string.
    std::string getShapeAsUnicode() const;
};

#endif // TILE_H