#ifndef _INPUTHANDLER_HPP
#define _INPUTHANDLER_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "command.hpp"
#include "interactCommand.hpp"
#include "moveCommand.hpp"
#include "objectStorage.hpp"
#include "math.h"
#include "selectedCommand.hpp"
#include "exitCommand.hpp"

class inputHandler{
private:
    std::array<sf::Keyboard::Key, 2>  moveKeys = {
        sf::Keyboard::Left, sf::Keyboard::Right
    };

    std::array<sf::Keyboard::Key, 2> interactionKeys ={
        sf::Keyboard::E,
        sf::Keyboard::Up
    };

    std::array<sf::Mouse::Button, 2> selectKeys = {
        sf::Mouse::Left, sf::Mouse::Right
    };

    std::array<sf::Keyboard::Key,1> exitKeys = {
        sf::Keyboard::Key::Escape
    };

    objectStorage &gameObjectStorage;

    float currentDistance(std::shared_ptr<gameObject> objectPointer){
        sf::Vector2f mainCharPosition = gameObjectStorage.character1->getSprite().getPosition();
        sf::Vector2f objectPosition = objectPointer->getSprite().getPosition();
        
        sf::Vector2f characterPosCorrectionVector = sf::Vector2f( gameObjectStorage.character1->getSprite().getGlobalBounds().width *0.5, gameObjectStorage.character1->getSprite().getGlobalBounds().height *0.5);
        sf::Vector2f objectPosCorrectionVector = sf::Vector2f( objectPointer->getSprite().getGlobalBounds().width *0.5, objectPointer->getSprite().getGlobalBounds().height *0.5);

        mainCharPosition += characterPosCorrectionVector;
        objectPosition += objectPosCorrectionVector;

        return sqrt( pow(objectPosition.x - mainCharPosition.x, 2) + pow(objectPosition.y - mainCharPosition.y, 2) );
    }

    bool inRange(std::shared_ptr<gameObject> objectPointer){
        return currentDistance(objectPointer) <= 200;
    }
    
    

public:

    inputHandler(objectStorage &gameObjectStorage):
        gameObjectStorage{gameObjectStorage}
    {
    }

    std::unique_ptr<command> handleInput(){

        // for dungeonGamestate
        for( auto movementKey : moveKeys){
            if(sf::Keyboard::isKeyPressed(movementKey)){
                std::unique_ptr<command>( new moveCommand( movementKey, gameObjectStorage.character1));
            }
        }

        //for dungeonGamestate
        for( auto interactKey : interactionKeys){
            if(sf::Keyboard::isKeyPressed(interactKey)){

                std::shared_ptr<gameObject> closestInteractablePointer = nullptr;

                for(std::shared_ptr<gameObject> interactableObject : *gameObjectStorage.getActive()){
                    if(interactableObject->isInteractable() && inRange(interactableObject)){
                        closestInteractablePointer = interactableObject;
                    }
                }

                for(std::shared_ptr<gameObject> objectPointer : *gameObjectStorage.getActive()){

                    if(objectPointer->isInteractable() && inRange(objectPointer) && (currentDistance(objectPointer) < currentDistance(closestInteractablePointer) && closestInteractablePointer != nullptr)){
                        closestInteractablePointer = objectPointer;
                    }

                }
                
                if(closestInteractablePointer != nullptr){
                    return std::unique_ptr<command>(new interactCommand(closestInteractablePointer));
                }
                else{
                    return NULL;
                }
            }
        }

        for(auto exitKey : exitKeys){
            if(sf::Keyboard::isKeyPressed(exitKey)){
                return std::unique_ptr<command>( new exitCommand());
            }
        }

        for( auto i : moveKeys){
            if(sf::Keyboard::isKeyPressed(i)){
                return std::unique_ptr<command>(new moveCommand( i, gameObjectStorage.character1));
            }
        }


        for( auto i : selectKeys ){
            if(sf::Mouse::isButtonPressed(i)){
                sf::Vector2i position = sf::Mouse::getPosition();
                for( auto i : *gameObjectStorage.getActive() ){
                    if( i->isInteractable() && i->getSprite().getGlobalBounds().contains(sf::Vector2f(position.x, position.y))){
                        std::cout << "interctable found" << std::endl;
                        return std::unique_ptr<command>( new selectedCommand(i));
                    }
                }
            }
        }

    return NULL;
    }
};


#endif