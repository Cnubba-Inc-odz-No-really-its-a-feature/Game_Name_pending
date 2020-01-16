#ifndef _CHEST_HPP
#define _CHEST_HPP

#include "gameObject.hpp"
#include "memory"
#include "objectStorage.hpp"
#include <iostream>

class chest: gameObject{
private:
    sf::RectangleShape chestRectangle;
    std::vector<gameObject> lootVector;
    bool open;
public:
    chest(const sf::Vector2f& position):
        chestRectangle{position}
    {
        chestRectangle.setFillColor(sf::Color::Red);
        chestRectangle.setPosition(position);
        chestRectangle.setSize( sf::Vector2f(200,125) );
        interactable = true;
    }

    void interact() override{
        std::cout << "chest has been interacted with: "  << objectID << std::endl;
    }

    void interact(objectStorage& objectStorage, const float& mainCharacterPosition{

    }

    void draw(sf::RenderWindow& window) override{
        window.draw(chestRectangle);
        if(open){
            for(auto& loot : lootVector){
                loot.draw(window);
            }
        }
    }

    void move(sf::Vector2f delta) override{}
};

#endif