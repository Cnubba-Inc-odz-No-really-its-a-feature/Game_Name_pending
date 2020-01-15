#ifndef _INPUTHANDLER_HPP
#define _INPUTHANDLER_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "command.hpp"
#include "interactCommand.hpp"
#include "moveCommand.hpp"
#include "objectStorage.hpp"
#include "math.h"

class inputHandler{
private:
    std::array<sf::Keyboard::Key, 4>  moveKeys = {
        sf::Keyboard::Up, sf::Keyboard::Down,
        sf::Keyboard::Left, sf::Keyboard::Right
    };

    std::array<sf::Keyboard::Key, 2> interactionKeys ={
        sf::Keyboard::E,
        sf::Keyboard::Up
    };

    objectStorage &inputStorage;

    std::shared_ptr<gameObject> mainCharacter;

    float currentDistance(std::shared_ptr<gameObject> objectPointer){
        sf::Vector2f mainCharPosition = mainCharacter->getPosition();
        sf::Vector2f objectPosition = objectPointer->getPosition();
        
        return sqrt( pow(objectPosition.x - mainCharPosition.x, 2) + pow(objectPosition.y - mainCharPosition.y, 2) );
    }

    bool inRange(std::shared_ptr<gameObject> objectPointer){
        return currentDistance(objectPointer) <= 20;
    }
    
public:

    inputHandler(objectStorage &inputStorage):
    inputStorage(inputStorage){}

    command* handleInput(){

        for( auto movementKey : moveKeys){
            if(sf::Keyboard::isKeyPressed(movementKey)){
                auto j = inputStorage.get()[0]; //get matthies info
                return new moveCommand( movementKey, inputStorage.getObject() );
            }
        }

        for( auto interactKey : interactionKeys){
            if(sf::Keyboard::isKeyPressed(interactKey)){

                for(std::shared_ptr<gameObject> objectPointer : inputStorage.game){

                    std::shared_ptr<gameObject> closestInteractablePointer = NULL; //needs to be changed to a "nullObject" ie distance = infinite
                    if(objectPointer->interactable && inRange(objectPointer) && currentDistance(objectPointer) < currentDistance(closestInteractablePointer)){
                        closestInteractablePointer = objectPointer;
                    }

                    return new interactCommand(closestInteractablePointer);
                }

            }
        }


    return NULL;
    }
};

#endif