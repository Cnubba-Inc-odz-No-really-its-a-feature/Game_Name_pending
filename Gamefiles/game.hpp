#ifndef _GAME_HPP
#define _GAME_HPP

#include <SFML/Graphics.hpp>
#include <ctime>
#include "renderer.hpp"
#include "inputHandler.hpp"
#include "factory.hpp"

class game{
private:
    sf::RenderWindow& gameWindow;

    objectStorage gameObjectStorage;
    renderer gameObjectRenderer;
    inputHandler gameInputHandler;
    factory gameObjectFactory;

    int MS_PER_FRAME = 100;
    int lag = 0;

    clock_t clockNow;
    clock_t clockPrevious;


public:

    game(sf::RenderWindow& gameWindow):
        gameWindow(gameWindow),
        gameObjectRenderer(gameWindow, gameObjectStorage),
        gameInputHandler(gameObjectStorage),
        gameObjectFactory(gameObjectStorage, gameWindow)
    {
        gameObjectFactory.factorNewGameState("gameState1.txt");
    }

    void gameLoop();


};



#endif

