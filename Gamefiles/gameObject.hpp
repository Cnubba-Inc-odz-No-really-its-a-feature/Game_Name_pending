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
    bool interactable;

public:
    int priority;
    gameObject(sf::Vector2f position, sf::Vector2f scale, std::map<std::string, sf::Texture> textureMap);
    gameObject();
    virtual ~gameObject();
    bool isInteractable();
    sf::Sprite getSprite();
    virtual void interact() = 0;
    virtual void draw(sf::RenderWindow& window) =0;
    virtual void move(sf::Vector2f delta) = 0;
    virtual void update() = 0;

};

#endif