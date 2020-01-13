#include "game.hpp"



int main(){
    sf::RenderWindow window{ sf::VideoMode{ 1800, 1000 }, "SFML window" };
    game mainGame(window);
    mainGame.gameLoop();


    return 0;

}