#ifndef _INPUTHANDLER_HPP
#define _INPUTHANDLER_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "command.hpp"
#include "exitCommand.hpp"
#include "interactCommand.hpp"
#include "math.h"
#include "chrono"
#include "moveCommand.hpp"
#include "objectStorage.hpp"
#include "selectedCommand.hpp"
#include "endTurnCommand.hpp"
#include "cardSelectCommand.hpp"
#include "fightController.hpp"
#include "deckEditorButtonCommand.hpp"
#include "macrodefinitions.hpp"


///\brief
/// handles all the input
///\details
/// every frame the inputhandler is called and returns a command if nesessery.
class inputHandler {
 private:
  std::array<sf::Keyboard::Key, 2> moveKeys = {sf::Keyboard::Left, sf::Keyboard::Right};

  std::array<sf::Keyboard::Key, 2> interactionKeys = {sf::Keyboard::E, sf::Keyboard::Up};

  std::array<sf::Mouse::Button, 2> selectKeys = {sf::Mouse::Left, sf::Mouse::Right};

  std::array<sf::Keyboard::Key, 1> exitKeys = {sf::Keyboard::Key::Escape};

  objectStorage &gameObjectStorage;
  fightController& fightControlPointer;
  uint64_t lastInput;
  uint64_t lastEndTurn;

  std::shared_ptr<bool> allowEndTurn;
  
  ///\brief
  /// Checks if a command is valid
  bool isCommandValid(std::shared_ptr<command> command){
    return command != NULL;
  }

  ///\brief
  /// Checks if a combatcommand is valid
  bool isCombatCommandValid(std::shared_ptr<command> command, uint64_t& lastInput){
    if(lastInput + 100 < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() && command != NULL){

      lastInput = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
      return true;
    }
    return false;
  }

  ///\brief
  /// Calculates the distance between an object and the character
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

  ///\brief
  /// returns true if the char is close enough to the given pointer
  bool inRange(std::shared_ptr<gameObject> objectPointer) {
    return currentDistance(objectPointer) <= 200;
  }

  ///\brief
  /// Handles movement while in the dungeon
  std::shared_ptr<command> handleDungeonMovement(){
    for (auto movementKey : moveKeys) {
        if (sf::Keyboard::isKeyPressed(movementKey)) {
          return std::shared_ptr<command>(new moveCommand(movementKey, gameObjectStorage.character1));
        }
    }
    return NULL;
  }

  ///\brief
  /// Handles button presses
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

  ///\brief
  /// Returns exit command which when executed closes the game
  std::shared_ptr<command> handleExit(){
    for (auto exitKey : exitKeys) {
      if (sf::Keyboard::isKeyPressed(exitKey)) {
        gameObjectStorage.saveObjects();
        return std::shared_ptr<command>(new exitCommand(gameObjectStorage));
      }
    }
    return NULL;
  }
  
  ///\brief
  /// Handles clickes while in the dungeon
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

  ///\brief
  /// Handles clickes while in the deck editor
  std::shared_ptr<command> handleDeckEditorClickSelect(){
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i position = sf::Mouse::getPosition();
        for(int i = 0; i < 10 ; i++){
          if(gameObjectStorage.editorUPButtonArray[i].getGlobalBounds().contains(
            sf::Vector2f(position.x, position.y))){
              return std::shared_ptr<command>(new deckEditorButtonCommand(gameObjectStorage, i, 1));
          }else if(gameObjectStorage.editorDOWNButtonArray[i].getGlobalBounds().contains(
            sf::Vector2f(position.x, position.y))){
              return std::shared_ptr<command>(new deckEditorButtonCommand(gameObjectStorage, i, -1));
            }
        }
      }
      return NULL;
    }

  ///\brief
  /// Handles clickes while in combat
  std::shared_ptr<command> handleCombatClickSelect(){
    if(*allowEndTurn.get()){
      for (auto i : selectKeys) {
        if (sf::Mouse::isButtonPressed(i)) {
            std::shared_ptr<unit> cardUnit = gameObjectStorage.cardHand.checkForCardPlay(sf::Mouse::getPosition(), fightControlPointer.playerMana, fightControlPointer.getSkyOpen(), fightControlPointer.getGroundOpen() );
            if(cardUnit != nullptr){
              return std::shared_ptr<command>(new cardSelectCommand(fightControlPointer, cardUnit));
            }
        }
      }
    }
    return NULL;
  }

  ///\brief
  /// Handles to end turn button
  std::shared_ptr<command> handleEndTurnButton(){
    if(*allowEndTurn.get()){

      lastEndTurn =  std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

      if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(fightControlPointer.isDoneButtonPressed(sf::Mouse::getPosition())){
          *allowEndTurn.get() = false;
          return std::shared_ptr<command>(new endTurnCommand(fightControlPointer, allowEndTurn));
        }
     }
    }
    return NULL;
  }

  ///\brief
  /// Handles commands while in the dungeon
  std::shared_ptr<command> handleDungeonCommands(uint64_t& lastInput){
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

  ///\brief
  /// Handles commands while in the fight
  std::shared_ptr<command> handleCombatCommands(uint64_t& lastInput){
        
        std::shared_ptr<command> obtainedCommand;

        if(*allowEndTurn.get()){
          obtainedCommand = handleCombatClickSelect();
          if(isCombatCommandValid(obtainedCommand, lastInput)){
            return obtainedCommand;
          }
          obtainedCommand = handleEndTurnButton();
          if(isCombatCommandValid(obtainedCommand, lastInput)){
            return obtainedCommand;
          }
        }

        obtainedCommand = handleExit();
        if(isCombatCommandValid(obtainedCommand, lastInput)){
          return obtainedCommand;
        }
        return NULL;
  }

  ///\brief
  /// Handles commands while in the dungeon
  std::shared_ptr<command> handleDeckEditorCommands(){
      std::shared_ptr<command> obtainedCommand;
      obtainedCommand = handleDeckEditorClickSelect();
      if(isCommandValid(obtainedCommand)){
          return obtainedCommand;
      }

      obtainedCommand = handleDungeonClickSelect();
        if(isCommandValid(obtainedCommand) && gameObjectStorage.deckEditor.getDeckSize() == 22){
          return obtainedCommand;
      }
      return NULL;
  }
  

 public:
  ///\brief
  /// Constructor that saves storage and fightcontrol so it can send the commands to the right objects
  inputHandler(objectStorage &gameObjectStorage, fightController& fightControlPointer)
      : gameObjectStorage{gameObjectStorage},
        fightControlPointer{fightControlPointer},
        allowEndTurn{std::make_shared<bool>(true)}
       {
         lastInput = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
         lastEndTurn = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
       }

  ///\brief
  /// Gets called every frame and depending on the active state calls its sub functions
  std::shared_ptr<command> handleInput() {
      switch(gameObjectStorage.keyActive.at(0)){
        case 'r':
          return handleDungeonCommands(lastInput);
          break;
        case 'c':
          return handleCombatCommands(lastInput);
          break;
        case 'd':
          return handleDeckEditorCommands();
          break;
        default:
          return handleDungeonCommands(lastInput);
          break;
      }
  }


};

#endif