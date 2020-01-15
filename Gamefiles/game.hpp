#ifndef _GAME_HPP
#define _GAME_HPP
#include <SFML/Graphics.hpp>
#include <ctime>
#include "renderer.hpp"
#include "inputHandler.hpp"
#include "factory.hpp"

class game{
private:
    sf::RenderWindow& window;

    objectStorage storage;
    renderer objectRenderer;
    inputHandler gameInputHandler;

    time_t timerPrevious;
    time_t timerCurrent;
    int MS_PER_FRAME = 2000;
    int lag = 0;
public:

    game(sf::RenderWindow& window):
        window(window),
        objectRenderer(window, storage),
        gameInputHandler(storage)
    
    {

        auto fact = factory(storage, window);
        std::cout<<(*storage.game).size()<<std::endl;


    }

    void gameLoop();


};



#endif

