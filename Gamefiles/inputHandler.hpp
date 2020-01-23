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

class inputHandler {
 private:
  std::array<sf::Keyboard::Key, 2> moveKeys = {sf::Keyboard::Left,
                                               sf::Keyboard::Right};

  std::array<sf::Keyboard::Key, 2> interactionKeys = {sf::Keyboard::E,
                                                      sf::Keyboard::Up};

  std::array<sf::Mouse::Button, 2> selectKeys = {sf::Mouse::Left,
                                                 sf::Mouse::Right};

  std::array<sf::Keyboard::Key, 1> exitKeys = {sf::Keyboard::Key::Escape};

  objectStorage &gameObjectStorage;

  float currentDistance(std::shared_ptr<gameObject> objectPointer) {
    sf::Vector2f mainCharPosition =
        gameObjectStorage.character1->getSprite().getPosition();
    auto width =
        gameObjectStorage.character1->getSprite().getGlobalBounds().width;
    auto height =
        gameObjectStorage.character1->getSprite().getGlobalBounds().height;
    sf::Vector2f compensationVector = sf::Vector2f(width * 0.5, height * 0.5);
    mainCharPosition += compensationVector;

    sf::Vector2f objectPosition = objectPointer->getSprite().getPosition();
    return sqrt(pow(objectPosition.x - mainCharPosition.x, 2) +
                pow(objectPosition.y - mainCharPosition.y, 2));
  }

  bool inRange(std::shared_ptr<gameObject> objectPointer) {
    return currentDistance(objectPointer) <= 200;
  }

 public:
  inputHandler(objectStorage &gameObjectStorage)
      : gameObjectStorage{gameObjectStorage} {}

  std::unique_ptr<command> handleInput() {
    // for dungeonGamestate
    if (gameObjectStorage.keyActive.at(0) == 'r') {
      for (auto movementKey : moveKeys) {
        if (sf::Keyboard::isKeyPressed(movementKey)) {
          std::unique_ptr<command>(
              new moveCommand(movementKey, gameObjectStorage.character1));
        }
      }

      for (auto i : moveKeys) {
        if (sf::Keyboard::isKeyPressed(i)) {
          return std::unique_ptr<command>(
              new moveCommand(i, gameObjectStorage.character1));
        }
      }
    }

    // for dungeonGamestate
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
          return std::unique_ptr<command>(
              new interactCommand(closestInteractablePointer));
        } else {
          return NULL;
        }
      }
    }

    for (auto exitKey : exitKeys) {
      if (sf::Keyboard::isKeyPressed(exitKey)) {
        return std::unique_ptr<command>(new exitCommand());
      }
    }

    for (auto i : selectKeys) {
      if (sf::Mouse::isButtonPressed(i)) {
        sf::Vector2i position = sf::Mouse::getPosition();
        for (auto j : *gameObjectStorage.getActive()) {
          if (j->isInteractable() &&
              j->getSprite().getGlobalBounds().contains(
                  sf::Vector2f(position.x, position.y))) {
            return std::unique_ptr<command>(new selectedCommand(j));
          }
        }
      }
    }

    return NULL;
  }
};

#endif