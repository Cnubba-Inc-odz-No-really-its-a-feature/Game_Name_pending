#ifndef _GAME_HPP
#define _GAME_HPP

#include <SFML/Graphics.hpp>
#include "renderer.hpp"
#include "inputHandler.hpp"
#include "fightController.hpp"
#include <chrono>
#include <cstdint>

class game{
private:
    sf::RenderWindow& gameWindow;
    objectStorage gameObjectStorage;
    fightController fightControl;
    renderer gameObjectRenderer;
    inputHandler gameInputHandler;

    uint64_t MS_PER_FRAME = 1000 / 60;
    uint64_t loopTime = 0;

public:

    game(sf::RenderWindow& gameWindow, char state = 'C'):
        gameWindow(gameWindow),
        gameObjectStorage(gameWindow),
        fightControl(gameObjectStorage.cardHand),
        gameObjectRenderer(gameWindow, gameObjectStorage, fightControl),
        gameInputHandler(gameObjectStorage, fightControl)
    {}

    void gameLoop();


};



#endif

