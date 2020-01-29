#ifndef _GAMEOBJECT_HPP
#define _GAMEOBJECT_HPP

#include "string"
#include "iostream"
#include "memory"
#include <SFML/Graphics.hpp>
#include <string>


class gameObject{
protected:
    std::string objectID;
    int objectTypeID;
    sf::Sprite objectSprite;
    sf::Texture spriteTexture;
    std::map<std::string, sf::Texture> textureMap;
    bool interactable = false;
    friend class lootObject;
    std::string type;


    bool isHovering(){
        return objectSprite.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
    }

public:

    gameObject(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, int objectPriority =0): 
        textureMap(textureMap),
        objectPriority(objectPriority)
    {
        firstkey = firstKey;
        objectSprite.setPosition(spritePosition);
        objectSprite.setScale(spriteScale.x, spriteScale.y);
        spriteTexture = textureMap[firstKey];
        objectSprite.setTexture(spriteTexture);
        objectID = 5;
    }

    gameObject(){}

    virtual ~gameObject(){}

    std::string soundFile;
    std::string textureFile;
    std::string firstkey;
    std::string secondkey;
    std::string target;
    bool interacted = false;
    int objectPriority;
    bool isInteractable(){ return interactable; }
    sf::Sprite getSprite(){ return objectSprite; }
    std::string getObjectID(){ return objectID; }
    std::string getType(){ return type; }
    virtual void interact() = 0;
    virtual void draw(sf::RenderWindow& gameWindow) =0;
    virtual void setTarget(std::string newTarget){};
    virtual void move(sf::Vector2f moveDirection) = 0;
    virtual void jumpLocationTo(sf::Vector2f jumpLocation){};
    virtual void update() = 0;

    virtual void setFrame(int maxFrame, int textureRow) =0;
};

#endif