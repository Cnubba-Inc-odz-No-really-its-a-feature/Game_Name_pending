#ifndef _CHEST_HPP
#define _CHEST_HPP

#include "gameObject.hpp"
#include "memory"
#include <iostream>

class chest: gameObject{
private:
    sf::RectangleShape chestRectangle;
public:
    chest(const sf::Vector2f& position):
        chestRectangle{position}
    {
        chestRectangle.setFillColor(sf::Color::Red);
        chestRectangle.setPosition(position);
        chestRectangle.setSize( sf::Vector2f(200,125) );
    }

    void interact() override{
        std::cout << "chest has been interacted with: "  << objectID << std::endl;
    }

    void draw(sf::RenderWindow& window) override{
        window.draw(chestRectangle);
    }

    void move(sf::Vector2f delta) override{}
};

#endif