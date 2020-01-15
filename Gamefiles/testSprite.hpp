#ifndef _TESTSPRITE_HPP
#define _TESTSPRITE_HPP
#include "gameObject.hpp"
#include "SFML/Graphics.hpp"

class textureSprite : public gameObject{
private:
    sf::Sprite sprite;
    std::map<std::string, sf::Texture> textureMap;
public:
    textureSprite(sf::Vector2f pos, sf::Vector2f size, std::map<std::string, sf::Texture> textureMap, int priority):
    gameObject(priority), textureMap(textureMap){
        sprite.setPosition(pos);
        sprite.setScale(size.x, size.y);
        sprite.setTexture(textureMap["texture1"]);
    }

    void draw(sf::RenderWindow& window){
        window.draw(sprite);

    }

    void move(sf::Vector2f delta){
        sprite.setPosition(sprite.getPosition()+delta);
    }
};

#endif