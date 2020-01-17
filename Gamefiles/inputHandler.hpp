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
    std::array<sf::Keyboard::Key, 2>  moveKeys = {
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
                command* newMoveCommand = new moveCommand( i, inputStorage.character1);
                return newMoveCommand;
            }
        }

        for( auto i : selectKeys ){
            if(sf::Mouse::isButtonPressed(i)){
                sf::Vector2i position = sf::Mouse::getPosition();
                sf::Vector2f mouseRectPos;
                mouseRectPos.x = position.x;
                mouseRectPos.y = position.y;
                auto objects = inputStorage.game.get();
                sf::FloatRect mousePosition(mouseRectPos, mouseRectPos);
                for( auto i : *objects ){
                    if(i.get()->isInteractable()){
                        if( i.get()->getSprite().getGlobalBounds().intersects(mousePosition)  ){
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