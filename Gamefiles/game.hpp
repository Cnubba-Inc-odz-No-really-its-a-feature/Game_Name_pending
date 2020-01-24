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
    renderer gameObjectRenderer;
    objectStorage gameObjectStorage;
    fightController fightControl;
    inputHandler gameInputHandler;

    uint64_t MS_PER_FRAME = 1000 / 60;
    uint64_t loopTime = 0;

public:

    game(sf::RenderWindow& gameWindow, char state = 'C'):
        gameWindow(gameWindow),
        gameObjectRenderer(gameWindow, gameObjectStorage),
        gameObjectStorage(gameWindow),
        fightControl(gameObjectStorage.getBoardContainer()),
        gameInputHandler(gameObjectStorage, std::make_shared<fightController>(fightControl))
    {}

    void gameLoop();


};



#endif

