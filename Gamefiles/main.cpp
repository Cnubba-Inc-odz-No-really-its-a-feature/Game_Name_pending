#include "game.hpp"
#include "objectStorage.hpp"



int main(){	
    sf::RenderWindow gameWindow{ sf::VideoMode{ 1920, 1080}, "SFML window", 8};
    game mainGame(gameWindow);
    mainGame.gameLoop();
    return 0;
}