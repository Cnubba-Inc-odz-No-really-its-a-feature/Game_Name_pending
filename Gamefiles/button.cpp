#include "button.hpp"

#include "gameObject.hpp"
#include <iostream>


button::button(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, int objectPriority):gameObject(spritePosition, spriteScale, textureMap, objectPriority)
{}

void button::draw(sf::RenderWindow& gameWindow){
    gameWindow.draw(objectSprite);
}

void button::setFrame(int maxFrame, int textureRow){}

void button::move(sf::Vector2f moveDirection){}

void button::update(){}
void button::interact(){}