#include "game.hpp"
#include "objectStorage.hpp"
#include "factory.hpp"


int main(){
    
    sf::RenderWindow gameWindow{ sf::VideoMode{ 1920, 1080}, "SFML window"};
    game mainGame(gameWindow);
    mainGame.gameLoop();
    return 0;

}