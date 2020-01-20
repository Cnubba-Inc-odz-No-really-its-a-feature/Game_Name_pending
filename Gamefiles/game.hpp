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

    game(sf::RenderWindow& gameWindow, char state = 'D'):
        gameWindow(gameWindow),
        gameObjectRenderer(gameWindow, gameObjectStorage),
        gameInputHandler(gameObjectStorage),
        gameObjectFactory(gameObjectStorage, gameWindow)
    {
        if(state == 'C'){
            gameObjectFactory.factorNewGameState("cardGame.txt");
        }else if(state == 'D'){
            gameObjectFactory.factorNewGameState("dungeon.txt");

        }
    }

    void gameLoop();


};



#endif

