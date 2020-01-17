#include "background.hpp"

background::background( sf::Vector2f position, sf::Vector2f scale, std::map<std::string, sf::Texture> textureMap, int prio):
    gameObject(position, scale, textureMap, prio)
{
}

void background::draw(sf::RenderWindow& window){
    std::cout << "im being drawn: background" << std::endl;
    window.draw(sprite);
}

void background::move(sf::Vector2f delta){}

void background::update(){
    // std::cout << "Hello" << std::endl;
    }

void background::interact(){}