#include "game.hpp"
#include "objectStorage.hpp"

///\image
/// images/Game.png

///\brief
///makes the window, constructs the game and starts the game loop, that never returns

int main(){	
    sf::RenderWindow gameWindow{ sf::VideoMode{ 1920, 1080}, "SFML window", 8};
    game mainGame(gameWindow);
    mainGame.gameLoop();
    return 0;
}