#ifndef _GAMEOBJECT_HPP
#define _GAMEOBJECT_HPP

#include "iostream"
#include "memory"
#include <SFML/Graphics.hpp>

class gameObject{
protected:
    int objectID;
    int typeID;
    sf::Sprite sprite;
    sf::Texture spriteTexture;
    std::map<std::string, sf::Texture> textureMap;
    bool interactable;
    friend class lootObject;

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
    bool isInteractable(){ return interactable; }
    sf::Vector2f getPosition(){ return sprite.getPosition(); }
    int getSize(){ return sprite.getScale().x; }

    // virtual void interact(){}
    sf::Sprite getSprite(){ return sprite; }
    virtual void interact() {};
    virtual void draw(sf::RenderWindow& window) {};
    virtual void move(sf::Vector2f delta) {};
    virtual void update() {};
    virtual void addToInventory(std::shared_ptr<gameObject> loot){};

};

#endif