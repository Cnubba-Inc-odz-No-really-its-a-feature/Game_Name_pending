#ifndef _CHEST_HPP
#define _CHEST_HPP

#include "gameObject.hpp"
#include "memory"
#include "lootObject.hpp"
#include "objectStorage.hpp"
#include <iostream>

class chest: public gameObject{
private:
    sf::RectangleShape chestRectangle;
    std::vector<lootObject> lootVector;
    bool open = false;
public:
    chest(sf::Vector2f position, sf::Vector2f scale, std::map<std::string, sf::Texture> textureMap, std::shared_ptr<gameObject> playerPointer, int prio):
        gameObject(position, scale, textureMap),
        chestRectangle{position}
    {
        chestRectangle.setFillColor(sf::Color::Red);
        chestRectangle.setPosition(position);
        chestRectangle.setSize( sf::Vector2f(200,125) );
        interactable = true;

        std::shared_ptr<gameObject> item0(new textureSprite(sf::Vector2f(position + sf::Vector2f(-100, -50)), sf::Vector2f(1,1), textureMap, 5));
        std::shared_ptr<gameObject> item1(new textureSprite(sf::Vector2f(position + sf::Vector2f(-100, -50)), sf::Vector2f(1,1), textureMap, 5));
        std::shared_ptr<gameObject> item2(new textureSprite(sf::Vector2f(position + sf::Vector2f(-100, -50)), sf::Vector2f(1,1), textureMap, 5));
        
        lootObject loot0 = lootObject(sf::Vector2f(position + sf::Vector2f(-100, -50)), playerPointer, item0);
        lootObject loot1 = lootObject(sf::Vector2f(position + sf::Vector2f(-100, -50)), playerPointer, item1);
        lootObject loot2 = lootObject(sf::Vector2f(position + sf::Vector2f(-100, -50)), playerPointer, item2);

        lootVector = {
            loot0, loot1, loot2
        };
    }

    void interact() override{
        // std::cout << "chest has been interacted with: "  << objectID << std::endl;
        // std::cout << "Segmentation fault (core dumped)" << std::endl;
        open = true;
        interactable = false;
        // exit(-1);
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

    void update(){}
    void setFrame(int max_frame){}
};

#endif