#ifndef _INPUTHANDLER_HPP
#define _INPUTHANDLER_HPP

#include "command.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include "moveCommand.hpp"
#include "gameStorage.hpp"

class inputHandler{
private:
    std::array<sf::Keyboard::Key, 4>  moveKeys = {
        sf::Keyboard::Up, sf::Keyboard::Down,
        sf::Keyboard::Left, sf::Keyboard::Right};
    gameStorage &inputStorage;
public:

    inputHandler(gameStorage &inputStorage):
    inputStorage(inputStorage){}

    command* handleInput(){

        for( auto i : moveKeys){
            if(sf::Keyboard::isKeyPressed(i)){
                auto j = inputStorage.get()[0];
                command* newMoveCommand = new moveCommand( i, inputStorage.getObject() );
                return newMoveCommand;
            }
        }


    return NULL;
    }
};

#endif