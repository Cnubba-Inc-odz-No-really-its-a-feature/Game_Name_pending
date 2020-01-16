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
    sf::Vector2f originalScale = sf::Vector2f(0,0);

public:
    gameObject(sf::Vector2f position, sf::Vector2f scale, std::map<std::string, sf::Texture> textureMap)
    {
        sprite.setPosition(position);
        sprite.setScale(scale.x, scale.y);
        //spriteTexture.loadFromFile(spriteTextureName);
        sprite.setTexture(textureMap["texture1"]);
    }

    gameObject(){}

    virtual ~gameObject(){}
    int priority;
    void resize(sf::Vector2f newSize, sf::Vector2f orig, sf::Vector2f old){
        if (originalScale.x == 0 && originalScale.x == 0)
        {
            originalScale.x = sprite.getScale().x;
            originalScale.y = sprite.getScale().y;
        }
        sprite.setScale((newSize.x/orig.x) * originalScale.x, (newSize.y/orig.y) * originalScale.y);
        sprite.setPosition(sf::Vector2f(sprite.getPosition().x * (newSize.x/old.x), sprite.getPosition().y * (newSize.y/old.x)));
    }
    bool isInteractable(){ return interactable; }
    sf::Sprite getSprite(){ return sprite; }
    virtual void interact() = 0;
    virtual void draw(sf::RenderWindow& window) =0;
    virtual void move(sf::Vector2f delta) = 0;
    virtual void update() = 0;

};

#endif