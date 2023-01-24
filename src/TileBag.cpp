#include "../include/TileBag.h"

TileBag::TileBag() {
    this->tileList = new LinkedList();
}

TileBag::TileBag(bool testFlag) {
    this->tileList = new LinkedList();
    fillTileBag();
    shuffleTileBag(testFlag);
}

TileBag::TileBag(const TileBag& other) {
    this->tileList = new LinkedList(*other.tileList);
}

TileBag::TileBag(TileBag&& other) {
    this->tileList = other.tileList;
    other.tileList = nullptr;
}

TileBag::~TileBag() {
    delete this->tileList;
    this->tileList = nullptr;
}

int TileBag::getNumOfTiles() const {
    return this->tileList->getLength();
}

bool TileBag::isEmpty() {
    bool isEmpty = false;
    if (getNumOfTiles() < 1) {
        isEmpty = true;
    }
    return isEmpty;
}

LinkedList* TileBag::getTileList() const {
    return this->tileList;
}

void TileBag::fillTileBag() {

    // Add shapes and colours to array for iteration.
    Colour colours[] = { RED, ORANGE, YELLOW, BLUE, PURPLE };
    Shape shapes[] = { CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER };

    // Add 2 of each colour and shape combination to the tile bag.
    for (int i = 0; i < sizeof(colours) / sizeof(Colour); i++) {
        for (int j = 0; j <sizeof(shapes) / sizeof(Shape); j++) {
            this->tileList->addEnd(new Tile(colours[i], shapes[j]));
            this->tileList->addEnd(new Tile(colours[i], shapes[j]));
        }
    }
}

void TileBag::shuffleTileBag(bool testFlag) {

    // Check if there are tiles in the tile bag.
    if (this->tileList->getLength() > 0) {
        LinkedList* tempTileList= new LinkedList();
        int totalTiles = this->tileList->getLength();

        // Shuffle tiles and put in temporary tile bag.
        for (int i = 0; i < totalTiles; i++) {

            // Generate a random number between min and max.
            int min = 1;
            int max = this->tileList->getLength();
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
            Tile *randomTile = this->tileList->getAtPos(randomVal);

            // Add tile to the temp tile bag.
            tempTileList->addEnd(new Tile(*randomTile));

            // Delete tile from original tile bag.
            this->tileList->deleteAtPos(randomVal);
        }
        // Clean up and point to new tile bag. 
        delete this->tileList;
        this->tileList = tempTileList;
        tempTileList= nullptr;
    }
}

void TileBag::addTile(Tile* tile) {
    this->tileList->addEnd(tile);
}

void TileBag::fillHand(LinkedList *hand) {
    while ((hand->getLength() < 6) && (this->tileList->getLength() > 0)) {

        // Draw a tile from the front of the tile bag. 
        Tile *tileDrawn = this->tileList->getFront();

        // Add it to the end of the player's hand. 
        hand->addEnd(new Tile(*tileDrawn));

        // Remove the tile from the tile bag.
        tileList->deleteFront();
    }
}

void TileBag::fillTilesArray(std::string tilesArray[], int* i) {

    // Convert tiles in the tile list to string and add to given array.                   
    for (int j = 1; j <= this->tileList->getLength(); j++) {
        tilesArray[*i] = this->tileList->getAtPos(j)->colour +
                         std::to_string(this->tileList->getAtPos(j)->shape);
        (*i)++;
    }
}