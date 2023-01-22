#include "../include/Tile.h"

Tile::Tile(Colour colour, Shape shape) {
    this->shape = Shape(shape);
    this->colour = Colour(colour);
}

Tile::Tile(const Tile& other) {
    this->shape = other.shape;
    this->colour = other.colour;
}

// Tile::Tile(Tile&& other) {
//     // TODO
// }

Tile::~Tile() {
}