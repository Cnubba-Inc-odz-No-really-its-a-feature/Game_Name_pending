#ifndef _GAMEOBJECT_HPP
#define _GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>

class gameObject{
protected:
    int objectID;
    int typeID;

    
    sf::Sprite sprite;
    sf::Texture spriteTexture;
    std::map<std::string, sf::Texture> textureMap;
    // bool interactable;

public:
    gameObject(sf::Vector2f position, sf::Vector2f scale, std::map<std::string, sf::Texture> textureMap)
    {
        sprite.setPosition(position);
        sprite.setScale(scale.x, scale.y);
        spriteTexture = textureMap["texture1"];
        sprite.setTexture(spriteTexture);
    }

    gameObject(){}

    virtual ~gameObject(){}
    int priority;
    // int objectID;
    // int typeID;
    int size;
    bool interactable;
    sf::Vector2f position;
    
    sf::Sprite objectSprite;

    bool isInteractable(){ return interactable; }
    sf::Vector2f getPosition(){ return position; }
    int getSize(){ return size; }

    // virtual void interact(){}
    sf::Sprite getSprite(){ return sprite; }
    virtual void interact() {};
    virtual void draw(sf::RenderWindow& window) {};
    virtual void move(sf::Vector2f delta) {};
    virtual void update() {};

};

#endif