#ifndef _INPUTHANDLER_HPP
#define _INPUTHANDLER_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "command.hpp"
#include "moveCommand.hpp"
#include "objectStorage.hpp"
#include "selectedCommand.hpp"

class inputHandler{
private:
    std::array<sf::Keyboard::Key, 4>  moveKeys = {
        sf::Keyboard::Up, sf::Keyboard::Down,
        sf::Keyboard::Left, sf::Keyboard::Right
    };

    std::array<sf::Mouse::Button, 2> selectKeys = {
        sf::Mouse::Left, sf::Mouse::Right
    };

    objectStorage &inputStorage;

public:

    inputHandler(objectStorage &inputStorage):
    inputStorage(inputStorage){}

    command* handleInput(){

        for( auto i : moveKeys){
            if(sf::Keyboard::isKeyPressed(i)){
                auto j = (*inputStorage.game)[0];
                command* newMoveCommand = new moveCommand( i, j );
                return newMoveCommand;
            }
        }

        for( auto i : selectKeys ){
            if(sf::Mouse::isButtonPressed(i)){
                sf::Vector2i position = sf::Mouse::getPosition();
                auto objects = inputStorage.game.get();
                for( auto i : *objects ){
                    if(i.get()->isInteractable()){
                        if( i.get()->getPosition().x <= position.x && int(i.get()->getPosition().x + i.get()->getSize()) >= position.x  
                        && int(i.get()->getPosition().y) <= position.y && int(i.get()->getPosition().x + i.get()->getSize()) >= position.y ){
                            command* newSelectedcommand = new selectedCommand(i);
                            return newSelectedcommand;
                        }
                    }
                }
            }
        }


    return NULL;
    }
};

#endif