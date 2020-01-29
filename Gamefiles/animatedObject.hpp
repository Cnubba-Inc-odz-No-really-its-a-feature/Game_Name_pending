#ifndef _ANIMATEDOBJECT_HPP
#define _ANIMATEDOBJECT_HPP
#include "gameObject.hpp"
#include "SFML/Graphics.hpp"

class animatedObject : public gameObject{
private:
    

public:


    animatedObject(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, int objectPriority, std::string textureFile, sf::Vector2f textureSheetDimensions):
    gameObject(spritePosition, spriteScale, textureMap, firstKey)
    {
        gameObject::textureFile = textureFile;
        gameObject::objectPriority = objectPriority;
        type = "TESTSPRITE_E";  
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