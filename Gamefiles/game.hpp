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
        std::cout << "1" << std::endl;
        auto fact = factory(storage);
        std::cout << "2" << std::endl;
        std::cout<<(*storage.title).size()<<std::endl;
        std::cout << "3" << std::endl;


    }

    void gameLoop();


};



#endif

