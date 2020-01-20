#include "background.hpp"

background::background( sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, int objectPriority):
    gameObject(spritePosition, spriteScale, textureMap, objectPriority)
{
}

void background::draw(sf::RenderWindow& gameWindow){
    gameWindow.draw(objectSprite);
}

void background::setFrame(int maxFrame, int textureRow){}

void background::move(sf::Vector2f moveDirection){}

void background::update(){
    }

void background::interact(){}