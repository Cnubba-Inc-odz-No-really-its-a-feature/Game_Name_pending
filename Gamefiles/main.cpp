#include "game.hpp"
#include "objectStorage.hpp"
#include "factory.hpp"


int main(){
    
    sf::RenderWindow window{ sf::VideoMode{ 1000, 1000 }, "SFML window" };
    game mainGame(window);
    mainGame.gameLoop();


    return 0;

}