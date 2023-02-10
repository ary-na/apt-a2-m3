#include "../include/Tile.h"

Tile::Tile(Colour colour, Shape shape) {
    this->shape = Shape(shape);
    this->colour = Colour(colour);
}

Tile::Tile(const Tile &other) {
    this->shape = other.shape;
    this->colour = other.colour;
}

Tile::Tile(Tile &&other) {
    this->shape = other.shape;
    this->colour = other.colour;
    other.shape = 0;
    other.colour = '\0';
}

Tile::~Tile() {}

std::string Tile::getAsStr() {
    std::string tileStr = this->colour + std::to_string(this->shape);
    return tileStr;
}

std::string Tile::getAsUnicodeAndColour(){
    std::string unicode = this->getShapeAsUnicode();
    return this->getColourAsColour(unicode);
}

std::string Tile::getColourAsColour(const std::string& unicode) const {
    std::string tileBackgroundColour;
    if (this->colour == RED) {
        tileBackgroundColour = "\x1b[41m" + unicode + "\x1b[0m";
    } else if (this->colour == ORANGE) {
        tileBackgroundColour = "\x1b[103m" + unicode + "\x1b[0m";
    } else if (this->colour == YELLOW) {
        tileBackgroundColour = "\x1b[43m" + unicode + "\x1b[0m";
    } else if (this->colour == GREEN) {
        tileBackgroundColour = "\x1b[42m" + unicode + "\x1b[0m";
    }else if (this->colour == BLUE) {
        tileBackgroundColour = "\x1b[44m" + unicode + "\x1b[0m";
    }else if (this->colour == PURPLE) {
        tileBackgroundColour = "\x1b[45m" + unicode + "\x1b[0m";
    }
    return tileBackgroundColour;
}

std::string Tile::getShapeAsUnicode() const {
    std::string tileShapeUnicode;
    if (this->shape == CIRCLE) {
        tileShapeUnicode = "●1";
    } else if (this->shape == STAR_4) {
        tileShapeUnicode = "✦2";
    } else if (this->shape == DIAMOND) {
        tileShapeUnicode = "♦3";
    } else if (this->shape == SQUARE) {
        tileShapeUnicode = "◼4";
    }else if (this->shape == STAR_6) {
        tileShapeUnicode = "✶5";
    }else if (this->shape == CLOVER) {
        tileShapeUnicode = "♣6";
    }
    return tileShapeUnicode;
}