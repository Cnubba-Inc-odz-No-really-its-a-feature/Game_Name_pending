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

    objectStorage &inputStorage;

    float currentDistance(std::shared_ptr<gameObject> objectPointer){
        std::cout << "currentDistance" << std::endl;
        sf::Vector2f mainCharPosition = inputStorage.character1->getSprite().getPosition();
        std::cout << "mainChar ok" << std::endl;
        sf::Vector2f objectPosition = objectPointer->getSprite().getPosition();
        
        std::cout << "getting distance" << std::endl;
        
        return sqrt( pow(objectPosition.x - mainCharPosition.x, 2) + pow(objectPosition.y - mainCharPosition.y, 2) );
    }

    bool inRange(std::shared_ptr<gameObject> objectPointer){
        std::cout << "checking if object inrange" << std::endl;
        return currentDistance(objectPointer) <= 200;
    }
    
    

public:

    inputHandler(objectStorage &inputStorage):
        inputStorage{inputStorage}
    {
    }

    command* handleInput(){

        // for dungeonGamestate
        for( auto movementKey : moveKeys){
            if(sf::Keyboard::isKeyPressed(movementKey)){
                std::cout << "creating move command" << std::endl;
                return new moveCommand( movementKey, inputStorage.character1);
            }
        }

        //for dungeonGamestate
        for( auto interactKey : interactionKeys){
            if(sf::Keyboard::isKeyPressed(interactKey)){
                std::cout << "searching for interactables" << std::endl;

                std::shared_ptr<gameObject> closestInteractablePointer = nullptr;

                for(std::shared_ptr<gameObject> interactableObject : *inputStorage.game){
                    if(interactableObject->isInteractable() && inRange(interactableObject)){
                        std::cout << "interactable found" << std::endl;
                        closestInteractablePointer = interactableObject;
                    }
                }

                for(std::shared_ptr<gameObject> objectPointer : *inputStorage.game ){

                    if(objectPointer->isInteractable() && inRange(objectPointer) && (currentDistance(objectPointer) < currentDistance(closestInteractablePointer) && closestInteractablePointer != nullptr)){
                        closestInteractablePointer = objectPointer;
                    }

                }
                
                if(closestInteractablePointer != nullptr){
                    return new interactCommand(closestInteractablePointer);
                }
                else{
                    return NULL;
                }
            }
        }

        for(auto exitKey : exitKeys){
            if(sf::Keyboard::isKeyPressed(exitKey)){
                return new exitCommand();
            }
        }

        
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
                        if( i->getSprite().getGlobalBounds().intersects(mousePosition)  ){
                            command* newSelectedcommand = new selectedCommand(i);
                            return newSelectedcommand;
                        }
                    }
                }
            }
        }

        // for( auto i : selectKeys ){
        //     if(sf::Mouse::isButtonPressed(i)){
        //         sf::Vector2i position = sf::Mouse::getPosition();
        //         auto objects = inputStorage.game.get();
        //         for( auto i : *objects ){
        //             if(i.get()->isInteractable()){
        //                 if( i.get()->getPosition().x <= position.x && int(i.get()->getPosition().x + i.get()->getSize()) >= position.x  
        //                 && int(i.get()->getPosition().y) <= position.y && int(i.get()->getPosition().x + i.get()->getSize()) >= position.y ){
        //                     command* newSelectedcommand = new selectedCommand(i);
        //                     return newSelectedcommand;
        //                 }
        //             }
        //         }
        //     }
        // }


    return NULL;
    }
};


#endif