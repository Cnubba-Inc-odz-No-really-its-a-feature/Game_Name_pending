#ifndef _BACKGROUND_HPP
#define _BACKGROUND_HPP

#include "gameObject.hpp"

class background : public gameObject{
private:
    std::vector<sf::Sprite> layerVector;
    int filledCount;

    void fillLayer(const std::string& filePath){
        spriteTexture.loadFromFile(filePath);
        sprite.setTexture(spriteTexture);
        sprite.setPosition(sf::Vector2f(-800,0));
        sprite.setScale(sf::Vector2f(10,10));
        layerVector.push_back(sprite);   
    }

public:
    background(const std::vector<std::string> filepaths)
    {        
        for (uint_fast8_t i = 0; i < filepaths.size(); i++){
            fillLayer(filepaths[i]);
        }
    }

    void draw(sf::RenderWindow& window) override{
        for(uint_fast8_t i = 0; i < layerVector.size(); i++){
            window.draw(layerVector[i]);
        }
    }

    void move(sf::Vector2f delta) override{
        for(uint_fast8_t i = 0; i < layerVector.size(); i++){
            sf::Vector2f position = layerVector[i].getPosition();
            sf::Vector2f newPosition = sf::Vector2f(position.x + delta.x * 0.25 * i ,position.y + delta.y * 0.10 * i);
            layerVector[i].setPosition(newPosition);
        }
    }
    void update()override{}
    void interact()override{}
        
};


#endif