#ifndef _BACKGROUND_HPP
#define _BACKGROUND_HPP

#include "gameObject.hpp"

class background : public gameObject{
private:
    std::vector<sf::Sprite> layerVector;
    int filledCount;
    
    void fillLayer(const std::string& filePath){
         
        sf::Sprite rect;
        sf::Texture texture;
        texture.loadFromFile(filePath);
        rect.setTexture(texture);
        rect.setPosition(sf::Vector2f(-800,0));
        rect.setScale(sf::Vector2f(10,10));
        layerVector.push_back(rect);   
    
    }

public:
    background(const std::vector<std::string> filepaths){
        
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
    
        
};


#endif