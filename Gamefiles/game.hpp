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
    /// \brief
    /// Saves a refrence to the window
    sf::RenderWindow& gameWindow;

    /// \brief
    /// Makes a global objectStorage object
    objectStorage gameObjectStorage;

    /// \brief
    /// keeps a fightcontroller to start fights in the dungeon with
    fightController fightControl;

    /// \brief
    /// calls the draw of all active objects every frame
    renderer gameObjectRenderer;

    /// \brief
    /// Generates input commands and sends them to the right objects
    inputHandler gameInputHandler;

    uint64_t MS_PER_FRAME = 1000 / 60;
    uint64_t loopTime = 0;

public:

    /// \brief
    /// Constructs all the nessesary building blocks of the game loop in the right order.
    game(sf::RenderWindow& gameWindow, char state = 'C'):
        gameWindow(gameWindow),
        gameObjectStorage(gameWindow),
        fightControl(gameObjectStorage.cardHand, gameObjectStorage),
        gameObjectRenderer(gameWindow, gameObjectStorage, fightControl),
        gameInputHandler(gameObjectStorage, fightControl)
    {}

    /// \brief
    /// Single call, will never return. Starts the game loop/engine of the game
    void gameLoop();
};



#endif

