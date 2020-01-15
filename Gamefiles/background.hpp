#ifndef _BACKGROUND_HPP
#define _BACKGROUND_HPP

#include "gameObject.hpp"

template<int layerCount>
class background : public gameObject{
private:
    std::array<sf::RectangleShape, layerCount> layerArray;
    int filledCount;
    
    void fillLayer(const std::string& filePath){
        if(filledCount <= layerCount){
            sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(0,0));
            sf::Texture texture;
            texture.loadFromFile(filePath)
            rect.setTexture(&texture);
            layerArray[filledCount] = rect;
            
            filledCount++;
        }
    }

public:
    background(const (&std::string)[layerCount] filepaths){
        filledCount = 0;
        
        for (std::string filepath : filepaths){
            fillLayer(filepath);
        }
    }

    void draw(sf::RenderWindow& window) override{
        for(uint_fast8_t i = 0; i < filledCount; i++){
            window.draw(layerArray[i])
        }
    }

    void move(sf::vector2f& delta) override{
        for(uint_fast8_t i = 0; i < filledCount; i++){
            sf::Vector2f position = layerArray[i].getPosition();
            sf::Vector2f newPosition = sf::Vector2f(position.x + delta.x * 0.25 * i ,position.y + delta.y * 0.25 * i);
            layerArray[i].setPosition(newPosition);
        }
    }
    
        
};


#endif