#include "inputHandler.hpp"

command* inputHandler::handleInput(){

        for( auto i : moveKeys){
            if(sf::Keyboard::isKeyPressed(i)){
                std::cout<< gameStorage.game.size() << std::endl;
                command* newMoveCommand = new moveCommand( i, gameStorage.game[0]);
                std::cout<<"command created" << std::endl;
                return newMoveCommand;
            }
        }


    return NULL;
}

