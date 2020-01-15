#ifndef _CHEST_HPP
#define _CHEST_HPP

#include "gameObject.hpp"
#include "memory"
#include <iostream>

class chest: gameObject{
private:
    sf::RectangleShape chestRectangle;
public:
    chest():
        chestRectangle{sf::RectangleShape(sf::Vector2f(200,120))}
    {
        chestRectangle.setFillColor(sf::Color::Red);
        chestRectangle.setPosition(sf::Vector2f(500,600));
    }

    void interact() override{
        std::cout << "chest has been interacted with: "  << objectID << std::endl;
    }

    void draw(sf::RenderWindow& window) override{
        window.draw(chestRectangle);
    }
};

#endif