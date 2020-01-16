#include "game.hpp"
#include "objectStorage.hpp"
#include "factory.hpp"


int main(){
    
    sf::RenderWindow window{ sf::VideoMode{ 1920, 1080, 8}, "SFML window", 8};
    game mainGame(window);
    mainGame.gameLoop();
    return 0;

}