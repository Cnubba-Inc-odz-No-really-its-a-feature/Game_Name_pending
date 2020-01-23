#ifndef _GAME_HPP
#define _GAME_HPP

#include <SFML/Graphics.hpp>
#include "renderer.hpp"
#include "inputHandler.hpp"
#include <chrono>
#include <cstdint>

class game{
private:
    sf::RenderWindow& gameWindow;
    renderer gameObjectRenderer;
    objectStorage gameObjectStorage;
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

