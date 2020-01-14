#ifndef _INPUTHANDLER_HPP
#define _INPUTHANDLER_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "command.hpp"
#include "moveCommand.hpp"
#include "objectStorage.hpp"

class inputHandler{
private:
    std::array<sf::Keyboard::Key, 2>  moveKeys = {
        sf::Keyboard::Left, sf::Keyboard::Right};
    objectStorage &gameStorage;

public:

    inputHandler(objectStorage &gameStorage):
        gameStorage(gameStorage){}

    command* handleInput();

};

#endif