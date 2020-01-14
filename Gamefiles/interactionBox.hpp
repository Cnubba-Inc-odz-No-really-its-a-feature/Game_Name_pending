#ifndef _INTERACTIONBOX_HPP
#define _INTERACTIONBOX_HPP
#include "SFML/Graphics.hpp"

class interactionBox{
private:
    sf::RectangleShape objectBox;
    
public:

    interactionBox(sf::Vector2f objectPosition, sf::Vector2f size){
        objectBox.setPosition(sf::Vector2f((objectPosition.x -60), (objectPosition.y + size.y - 5)));
        objectBox.setSize(sf::Vector2f((size.x + 120), 5));
        objectBox.setFillColor(sf::Color::Blue);
    };

    void draw(  sf::RenderWindow & window){
        window.draw(objectBox);
    }

    void move( sf::Vector2f delta){
        objectBox.setPosition(objectBox.getPosition() + delta);
    }

};


#endif