#ifndef _MOVECOMMAND_HPP
#define _MOVECOMMAND_HPP

#include "command.hpp"
#include <iostream>
#include <map>
#include "memory"

///\brief
/// Command that holds the object to move and the direction based on the key pressed

class moveCommand : public command{
private:
    sf::Keyboard::Key directionKey;
    std::shared_ptr<gameObject> objectToMove;

    std::map<sf::Keyboard::Key, sf::Vector2f> directionMap{ 
        {sf::Keyboard::Left, sf::Vector2f(-10.0, 0.0)},
        {sf::Keyboard::Right, sf::Vector2f(10.0, 0.0)}
    };
public:
    ///\brief
    /// Command that holds the object to move and the direction based on the key pressed
    moveCommand(sf::Keyboard::Key directionKey, std::shared_ptr<gameObject> objectToMove):
        directionKey(directionKey),
        objectToMove(objectToMove)
    {}

    ///\brief
    /// Executes the move command on the saved object
    void execute() override{
        objectToMove.get()->move(directionMap[directionKey]);
    }
    
};
#endif