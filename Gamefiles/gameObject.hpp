#ifndef _GAMEOBJECT_HPP
#define _GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>

class gameObject{
protected:
    int drawPriority;
    int objectID;
    int typeID;
    sf::Sprite sprite;
    sf::Texture spriteTexture;
    bool interactable;

public:
    gameObject(sf::Vector2f position, sf::Vector2f scale, std::string spriteTextureName)
    {
        sprite.setPosition(position);
        sprite.setScale(scale.x, scale.y);
        spriteTexture.loadFromFile(spriteTextureName);
        sprite.setTexture(spriteTexture);
    }

    gameObject(){}

    virtual ~gameObject(){}

    bool isInteractable(){ return interactable; }
    sf::Sprite getSprite(){ return sprite; }
    virtual void interact() = 0;
    virtual void draw(sf::RenderWindow& window) =0;
    virtual void move(sf::Vector2f delta) = 0;
    virtual void update() = 0;

};

#endif