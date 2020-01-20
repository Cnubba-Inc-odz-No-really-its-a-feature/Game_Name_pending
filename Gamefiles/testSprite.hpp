#ifndef _TESTSPRITE_HPP
#define _TESTSPRITE_HPP
#include "gameObject.hpp"
#include "SFML/Graphics.hpp"

class textureSprite : public gameObject{


public:
    textureSprite(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, int objectPriority):
    gameObject(spritePosition, spriteScale, textureMap, firstKey)
    {
        gameObject::objectPriority = objectPriority;
    }

    void draw(sf::RenderWindow& window){
        window.draw(objectSprite);

    }

    void move(sf::Vector2f moveDirection) override{
        objectSprite.setPosition(objectSprite.getPosition()+moveDirection);
    }

    void update(){}
    void interact(){}
    void setFrame(int maxFrame, int textureRow){}
};

#endif