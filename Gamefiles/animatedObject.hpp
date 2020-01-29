#ifndef _ANIMATEDOBJECT_HPP
#define _ANIMATEDOBJECT_HPP
#include "gameObject.hpp"
#include "SFML/Graphics.hpp"

class animatedObject : public gameObject{
private:
    sf::Vector2f textureSheetDimensions;
    sf::Vector2f textureFrameBounds;
    int textureFrame = 0;
    int frameCounter = 0;

public:


    animatedObject(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, int objectPriority, std::string textureFile, sf::Vector2f textureSheetDimensions):
    gameObject(spritePosition, spriteScale, textureMap, firstKey)
    {
        gameObject::textureFile = textureFile;
        gameObject::objectPriority = objectPriority;

        objectSprite.setTextureRect(sf::IntRect(textureFrameBounds.x*0, textureFrameBounds.y*0, textureFrameBounds.x, textureFrameBounds.y));
        objectSprite.setOrigin(objectSprite.getLocalBounds().left + (objectSprite.getLocalBounds().width/2), objectSprite.getLocalBounds().top + (objectSprite.getLocalBounds().height));

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