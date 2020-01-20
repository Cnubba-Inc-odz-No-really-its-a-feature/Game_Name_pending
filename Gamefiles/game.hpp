#ifndef _GAME_HPP
#define _GAME_HPP

#include <SFML/Graphics.hpp>
#include "renderer.hpp"
#include "inputHandler.hpp"
#include "factory.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>

class game{
private:
    sf::RenderWindow& gameWindow;

    objectStorage gameObjectStorage;
    renderer gameObjectRenderer;
    inputHandler gameInputHandler;
    factory gameObjectFactory;

    int MS_PER_FRAME = 1000 / 60;
    int lag = 0;



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

