#ifndef _GAMEOBJECT_HPP
#define _GAMEOBJECT_HPP

#include "iostream"
#include <SFML/Graphics.hpp>

class gameObject{
protected:
    int objectID;
    int objectTypeID;
    sf::Sprite objectSprite;
    sf::Texture spriteTexture;
    std::map<std::string, sf::Texture> textureMap;
    bool interactable;

    bool isHovering(){
        return objectSprite.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
    }

public:
    gameObject(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, int objectPriority =0): 
    textureMap(textureMap), objectPriority(objectPriority)
    {
        objectSprite.setPosition(spritePosition);
        objectSprite.setScale(spriteScale.x, spriteScale.y);
        spriteTexture = textureMap["texture1"];
        objectSprite.setTexture(spriteTexture);
    }

    gameObject(){}

    virtual ~gameObject(){}
    int objectPriority;
    bool isInteractable(){ return interactable; }
    sf::Sprite getSprite(){ return objectSprite; }
    virtual void interact() = 0;
    virtual void draw(sf::RenderWindow& gameWindow) =0;
    virtual void move(sf::Vector2f moveDirection) = 0;
    virtual void update() = 0;
    virtual void setFrame(int maxFrame, int textureRow) =0;

};

#endif