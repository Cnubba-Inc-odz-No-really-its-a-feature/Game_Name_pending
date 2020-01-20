#ifndef _MOVECOMMAND_HPP
#define _MOVECOMMAND_HPP

#include "command.hpp"
#include <iostream>
#include <map>
#include "memory"

class moveCommand : public command{
private:
    sf::Keyboard::Key directionKey;
    std::shared_ptr<gameObject> objectToMove;

    std::map<sf::Keyboard::Key, sf::Vector2f> directionMap{ 
        {sf::Keyboard::Left, sf::Vector2f(-2.0, 0.0)},
        {sf::Keyboard::Right, sf::Vector2f(2.0, 0.0)}
    };
public:
    moveCommand(sf::Keyboard::Key directionKey, std::shared_ptr<gameObject> objectToMove):
        directionKey(directionKey),
        objectToMove(objectToMove)
    {}

    void execute() override{
        objectToMove.get()->move(directionMap[directionKey]);
    }

    virtual void undo(){}
};
#endif