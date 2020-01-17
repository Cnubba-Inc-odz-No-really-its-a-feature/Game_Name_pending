#ifndef _TESTSPRITE_HPP
#define _TESTSPRITE_HPP
#include "gameObject.hpp"
#include "SFML/Graphics.hpp"

class textureSprite : public gameObject{


public:
    textureSprite(sf::Vector2f position, sf::Vector2f scale, std::map<std::string, sf::Texture> textureMap, int prio):
    gameObject(position, scale, textureMap){
        priority = prio;
    }

    void draw(sf::RenderWindow& window){
        window.draw(sprite);

    }

    void move(sf::Vector2f delta) override{
        sprite.setPosition(sprite.getPosition()+delta);
    }

    void update(){}
    void interact(){}
    void setFrame(int max_frame){}
};

#endif