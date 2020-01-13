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
        {sf::Keyboard::Left, sf::Vector2f(-1.0, 0.0)},
        {sf::Keyboard::Right, sf::Vector2f(1.0, 0.0)},
        {sf::Keyboard::Up, sf::Vector2f(0.0, -1.0)},
        {sf::Keyboard::Down, sf::Vector2f(0.0, 1.0)}
    };
public:
    moveCommand(sf::Keyboard::Key directionKey, std::shared_ptr<gameObject> objectToMove):
    directionKey(directionKey),
    objectToMove(objectToMove)
    {std::cout<<"moveCommand word aangemaakt"<<std::endl;;
    if(objectToMove == nullptr){
            std::cout<<"Object is nullptr in contrusctor moveCommand" << std::endl;
    }}

    void execute() override{
        std::cout<<"execute entered" << std::endl;
        if(objectToMove == nullptr){
            std::cout<<"Object is nullptr" << std::endl;
        }
        if(objectToMove.get() == nullptr){
            std::cout<<"pointer is nullpts" << std::endl;
        }
        objectToMove.get()->move(directionMap[directionKey]);
        std::cout<<"executed" << std::endl;
    }

    virtual void undo(){}
};
#endif