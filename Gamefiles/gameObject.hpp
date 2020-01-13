#ifndef _GAMEOBJECT_HPP
#define _GAMEOBJECT_HPP
#include <SFML/Graphics.hpp>

class gameObject{
public:
    gameObject(){}

    virtual ~gameObject(){}


    virtual void draw(sf::RenderWindow& window) =0;
    virtual void move(sf::Vector2f delta) = 0;

};

#endif