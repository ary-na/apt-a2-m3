#include "../include/TileBag.h"

TileBag::TileBag() {
    this->tileBagList = new LinkedList();
}

TileBag::TileBag(bool testFlag) {
    this->tileBagList = new LinkedList();
    fillTileBag();
    shuffleTileBag(testFlag);
}

TileBag::TileBag(const TileBag& other) {
    this->tileBagList = new LinkedList(*other.tileBagList);
}

TileBag::TileBag(TileBag&& other) {
    this->tileBagList = other.tileBagList;
    other.tileBagList = nullptr;
}

TileBag::~TileBag() {
    delete this->tileBagList;
    this->tileBagList = nullptr;
}

int TileBag::getNumOfTiles() const {
    return this->tileBagList->getLength();
}

bool TileBag::isEmpty() {
    bool isEmpty = false;
    if (getNumOfTiles() < 1) {
        isEmpty = true;
    }
    return isEmpty;
}

LinkedList* TileBag::getTileBagList() const {
    return this->tileBagList;
}

void TileBag::fillTileBag() {

    // Add shapes and colours to array for iteration.
    Colour colours[] = { RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE };
    Shape shapes[] = { CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER };

    // Add 2 of each colour and shape combination to the tile bag.
    for (int i = 0; i < sizeof(colours) / sizeof(Colour); i++) {
        for (int j = 0; j <sizeof(shapes) / sizeof(Shape); j++) {
            this->tileBagList->addEnd(new Tile(colours[i], shapes[j]));
            this->tileBagList->addEnd(new Tile(colours[i], shapes[j]));
        }
    }
}

void TileBag::shuffleTileBag(bool testFlag) {

    // Check if there are tiles in the tile bag.
    if (this->tileBagList->getLength() > 0) {
        LinkedList* tempTileList= new LinkedList();
        int totalTiles = this->tileBagList->getLength();

        // Shuffle tiles and put in temporary tile bag.
        for (int i = 0; i < totalTiles; i++) {

            // Generate a random number between min and max.
            int min = 1;
            int max = this->tileBagList->getLength();
            int randomVal = 0;
            std::uniform_int_distribution<int> uniform_dist(min, max);

            // If test flag is true, set seed 
            // to ensure consistent randomness.
            if(testFlag) {
                std::default_random_engine engine(2);
                randomVal = uniform_dist(engine);
            } else {
                std::random_device engine;
                randomVal = uniform_dist(engine);
            }
            // Get a tile from tile bag at random pos.
            Tile *randomTile = this->tileBagList->getAtPos(randomVal);

            // Add tile to the temp tile bag.
            tempTileList->addEnd(new Tile(*randomTile));

            // Delete tile from original tile bag.
            this->tileBagList->deleteAtPos(randomVal);
        }
        // Clean up and point to new tile bag. 
        delete this->tileBagList;
        this->tileBagList = tempTileList;
        tempTileList= nullptr;
    }
}

void TileBag::addTile(Tile* tile) {
    this->tileBagList->addEnd(tile);
}

void TileBag::fillHand(LinkedList *hand) {
    while ((hand->getLength() < 6) && (this->tileBagList->getLength() > 0)) {

        // Draw a tile from the front of the tile bag. 
        Tile *tileDrawn = this->tileBagList->getFront();

        // Add it to the end of the player's hand. 
        hand->addEnd(new Tile(*tileDrawn));

        // Remove the tile from the tile bag.
        tileBagList->deleteFront();
    }
}

void TileBag::addToArray(std::string tilesArray[], int* i) {
    this->tileBagList->addToArray(tilesArray, i);
}

std::string TileBag::getAsStr() {
    return this->tileBagList->getAsStr();
}