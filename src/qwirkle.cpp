#include "../include/Controller.h"
#include "../include/Game.h"
#include <iostream>
#include <memory>

int main(void) {

    std::unique_ptr<Controller> controller(new Controller);
    controller->launchGame();

    // Player* player1 = new Player("Carelle");
    // Player* player2 = new Player("Bob");

    // Game* game = new Game(player1, player2);

    // bool correctTiles = game->checkTiles(game->getPlayer1()->getHand(), 
    //                                      game->getPlayer2()->getHand(), 
    //                                      game->getBoard(), 
    //                                      game->GetTileBag());

    // std::cout << correctTiles << std::endl;

    return EXIT_SUCCESS;
}