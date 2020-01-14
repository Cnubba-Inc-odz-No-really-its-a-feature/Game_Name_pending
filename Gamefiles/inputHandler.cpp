#include "inputHandler.hpp"

command* inputHandler::handleInput(){

        for( auto i : moveKeys){
            if(sf::Keyboard::isKeyPressed(i)){

                command* newMoveCommand = new moveCommand( i, gameStorage.game[0]);
                return newMoveCommand;
            }
        }


    return NULL;
}

