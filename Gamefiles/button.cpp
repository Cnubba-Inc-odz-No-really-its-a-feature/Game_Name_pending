#include "button.hpp"

#include "gameObject.hpp"
#include <iostream>


button::button( sf::Vector2f position, sf::Vector2f scale, std::map<std::string, sf::Texture> textureMap, int prio):
    gameObject(position, scale, textureMap, prio)
{}

void button::draw(sf::RenderWindow& window){
    window.draw(sprite);
}

void button::setFrame(int max_frame, int row){}

void button::move(sf::Vector2f delta){}

void button::update(){}
void button::interact(){}