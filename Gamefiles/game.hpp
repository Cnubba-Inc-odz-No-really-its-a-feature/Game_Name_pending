#ifndef _GAME_HPP
#define _GAME_HPP

#include <SFML/Graphics.hpp>
#include "renderer.hpp"
#include "inputHandler.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>

class game{
private:
    sf::RenderWindow& gameWindow;
    objectStorage gameObjectStorage;
    renderer gameObjectRenderer;
    inputHandler gameInputHandler;

    uint64_t MS_PER_FRAME = 1000 / 60;
    uint64_t loopTime = 0;

public:

    game(sf::RenderWindow& gameWindow, char state = 'D'):
        gameWindow(gameWindow),
        gameObjectRenderer(gameWindow, gameObjectStorage),
        gameObjectStorage(gameWindow),
        gameInputHandler(gameObjectStorage)
    {}

    void gameLoop();


};



#endif

