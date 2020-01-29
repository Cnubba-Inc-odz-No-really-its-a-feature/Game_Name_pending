#ifndef _INPUTHANDLER_HPP
#define _INPUTHANDLER_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "command.hpp"
#include "exitCommand.hpp"
#include "interactCommand.hpp"
#include "math.h"
#include "moveCommand.hpp"
#include "objectStorage.hpp"
#include "selectedCommand.hpp"
#include "endTurnCommand.hpp"
#include "cardSelectCommand.hpp"
#include "fightController.hpp"
#include "deckEditorButtonCommand.hpp"

class inputHandler {
 private:
  std::array<sf::Keyboard::Key, 2> moveKeys = {sf::Keyboard::Left, sf::Keyboard::Right};

  std::array<sf::Keyboard::Key, 2> interactionKeys = {sf::Keyboard::E, sf::Keyboard::Up};

  std::array<sf::Mouse::Button, 2> selectKeys = {sf::Mouse::Left, sf::Mouse::Right};

  std::array<sf::Keyboard::Key, 1> exitKeys = {sf::Keyboard::Key::Escape};

  objectStorage &gameObjectStorage;
  std::shared_ptr<fightController> fightControlPointer;

  bool isCommandValid(std::shared_ptr<command> command){
    return command != NULL;
  }

  float currentDistance(std::shared_ptr<gameObject> objectPointer) {
    sf::Vector2f mainCharPosition = gameObjectStorage.character1->getSprite().getPosition();
    auto charWidth = gameObjectStorage.character1->getSprite().getGlobalBounds().width;
    auto charHeight = gameObjectStorage.character1->getSprite().getGlobalBounds().height;
    sf::Vector2f mainCharCompensationVector = sf::Vector2f(charWidth * 0.5, charHeight * 0.5);

    sf::Vector2f objectPosition = objectPointer->getSprite().getPosition();
    auto objWidth = objectPointer->getSprite().getGlobalBounds().width;
    auto objHeight = objectPointer->getSprite().getGlobalBounds().height;
    sf::Vector2f objectCompensationVector = sf::Vector2f(objWidth * 0.5, objHeight * 0.5);

    mainCharPosition += mainCharCompensationVector;
    objectPosition += objectCompensationVector;

    return sqrt(pow(objectPosition.x - mainCharPosition.x, 2) +  pow(objectPosition.y - mainCharPosition.y, 2));
  }

  bool inRange(std::shared_ptr<gameObject> objectPointer) {
    return currentDistance(objectPointer) <= 200;
  }

  std::shared_ptr<command> handleDungeonMovement(){
    for (auto movementKey : moveKeys) {
        if (sf::Keyboard::isKeyPressed(movementKey)) {
          return std::shared_ptr<command>(new moveCommand(movementKey, gameObjectStorage.character1));
        }
    }
    return NULL;
  }

  std::shared_ptr<command> handleButtonInteract(){
    for (auto interactKey : interactionKeys) {
      if (sf::Keyboard::isKeyPressed(interactKey)) {
        std::shared_ptr<gameObject> closestInteractablePointer = nullptr;

        for (std::shared_ptr<gameObject> interactableObject :
             *gameObjectStorage.getActive()) {
          if (interactableObject->isInteractable() &&
              inRange(interactableObject)) {
            closestInteractablePointer = interactableObject;
          }
        }

        for (std::shared_ptr<gameObject> objectPointer :
             *gameObjectStorage.getActive()) {
          if (objectPointer->isInteractable() && inRange(objectPointer) &&
              (currentDistance(objectPointer) <
                   currentDistance(closestInteractablePointer) &&
               closestInteractablePointer != nullptr)) {
            closestInteractablePointer = objectPointer;
          }
        }

        if (closestInteractablePointer != nullptr) {
          return std::shared_ptr<command>(
              new interactCommand(closestInteractablePointer));
        }
      }
    }
    return NULL;
  }

  std::shared_ptr<command> handleExit(){
    for (auto exitKey : exitKeys) {
      if (sf::Keyboard::isKeyPressed(exitKey)) {
        gameObjectStorage.saveObjects();
        return std::shared_ptr<command>(new exitCommand(gameObjectStorage));
      }
    }
    return NULL;
  }
  
  std::shared_ptr<command> handleDungeonClickSelect(){
    for (auto i : selectKeys) {
      if (sf::Mouse::isButtonPressed(i)) {
        sf::Vector2i position = sf::Mouse::getPosition();
        for (auto j : *gameObjectStorage.getActive()) {
          if (j->isInteractable() &&
              j->getSprite().getGlobalBounds().contains(
                  sf::Vector2f(position.x, position.y))) {
            return std::shared_ptr<command>(new selectedCommand(j));
          }
        }
      }
    }
    return NULL;
  }

  std::shared_ptr<command> handleDeckEditorClickSelect(){
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
      std::cout<<"mouse click noticed" << std::endl;
        sf::Vector2i position = sf::Mouse::getPosition();
        for(int i = 0; i < 10 ; i++){
          if(gameObjectStorage.editorUPButtonArray[i].getGlobalBounds().contains(
            sf::Vector2f(position.x, position.y))){
              std::cout<<"up button command found" << std::endl;
              return std::shared_ptr<command>(new deckEditorButtonCommand(gameObjectStorage, i, 1));
          }else if(gameObjectStorage.editorDOWNButtonArray[i].getGlobalBounds().contains(
            sf::Vector2f(position.x, position.y))){
              return std::shared_ptr<command>(new deckEditorButtonCommand(gameObjectStorage, i, -1));
            }
        }
      }
      return NULL;
    }

  std::shared_ptr<command> handleCombatClickSelect(){
    for (auto i : selectKeys) {
      if (sf::Mouse::isButtonPressed(i)) {
          std::shared_ptr<unit> cardUnit = gameObjectStorage.cardHand.checkForCardPlay(sf::Mouse::getPosition(), fightControlPointer->getSkyOpen(), fightControlPointer->getGroundOpen());
          if(cardUnit != nullptr){
            return std::shared_ptr<command>(new cardSelectCommand(fightControlPointer, cardUnit));
          }
      }

      // for clicking on menu buttons
      // sf::Vector2i position = sf::Mouse::getPosition();
      // for (auto j : *gameObjectStorage.getActive()) {
      //   if (j->isInteractable() && j->getSprite().getGlobalBounds().contains(sf::Vector2f(position.x, position.y))){
      //     return std::shared_ptr<command>(new selectedCommand(j));
      //   }
      // }
    }


    // if(gameObjectStorage.storageDeck.fightActive){
    //   if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
    //     auto x = gameObjectStorage.storageDeck.checkForCardPlay(sf::Mouse::getPosition());
    //     std::cout<<"found click" << std::endl;
    //   }
    // }

    return NULL;
  }

  std::shared_ptr<command> handleEndTurnButton(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
      return std::shared_ptr<command>(new endTurnCommand(fightControlPointer));
    }
    return NULL;
  }

  std::shared_ptr<command> handleDungeonCommands(){
        std::shared_ptr<command> obtainedCommand;

        obtainedCommand = handleDungeonMovement();
        if(isCommandValid(obtainedCommand)){
          return obtainedCommand;
        }
        obtainedCommand = handleButtonInteract();
        if(isCommandValid(obtainedCommand)){
          return obtainedCommand;
        }
        obtainedCommand = handleDungeonClickSelect();
        if(isCommandValid(obtainedCommand)){
          return obtainedCommand;
        }
        obtainedCommand = handleExit();
        if(isCommandValid(obtainedCommand)){
          return obtainedCommand;
        }

        return NULL;
  }

  std::shared_ptr<command> handleCombatCommands(){
        std::shared_ptr<command> obtainedCommand;

        obtainedCommand = handleCombatClickSelect();
        if(isCommandValid(obtainedCommand)){
          return obtainedCommand;
        }
        obtainedCommand = handleExit();
        if(isCommandValid(obtainedCommand)){
          return obtainedCommand;
        }
        obtainedCommand = handleEndTurnButton();
        if(isCommandValid(obtainedCommand)){
          return obtainedCommand;
        }
        return NULL;
  }

  std::shared_ptr<command> handleDeckEditorCommands(){
      std::shared_ptr<command> obtainedCommand;
      obtainedCommand = handleDeckEditorClickSelect();
      if(isCommandValid(obtainedCommand)){
          return obtainedCommand;
      }

      obtainedCommand = handleDungeonClickSelect();
        if(isCommandValid(obtainedCommand)){
          return obtainedCommand;
      }
      return NULL;
  }
  

 public:
  inputHandler(objectStorage &gameObjectStorage, std::shared_ptr<fightController> fightControlPointer)
      : gameObjectStorage{gameObjectStorage},
        fightControlPointer{fightControlPointer}
       {}

  std::shared_ptr<command> handleInput() {
    switch(gameObjectStorage.keyActive.at(0)){
      case 'r':
        return handleDungeonCommands();
        break;
      case 'c':
        return handleCombatCommands();
        break;
      case 'd':
        return handleDeckEditorCommands();
        break;
      default:
        return handleDungeonCommands();
        break;
    } 
  }
};

#endif