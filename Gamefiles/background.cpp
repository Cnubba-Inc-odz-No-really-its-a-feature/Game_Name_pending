#include "background.hpp"

background::background( sf::Vector2f position, sf::Vector2f scale, std::map<std::string, sf::Texture> textureMap, int prio):
    gameObject(position, scale, textureMap, prio)
{
}

void background::draw(sf::RenderWindow& window){
    window.draw(sprite);
}

void background::setFrame(int max_frame, int row){}

void background::move(sf::Vector2f delta){}

void background::update(){
    // std::cout << "Hello" << std::endl;
    }

void background::interact(){}