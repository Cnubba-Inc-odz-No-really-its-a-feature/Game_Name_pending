#include "button.hpp"
#include "gameObject.hpp"
#include <iostream>


button::button(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, int objectPriority)
:gameObject(spritePosition, spriteScale, textureMap, objectPriority), origScale(spriteScale), origPos(spritePosition)
{interactable = true;}

void button::draw(sf::RenderWindow& gameWindow){
    gameWindow.draw(objectSprite);
}

void button::setFrame(int maxFrame, int textureRow){}

void button::move(sf::Vector2f moveDirection){}

void button::update(){
    if (isHovering()){
        objectSprite.setScale(origScale.x * 1.2, origScale.y * 1.2);
        objectSprite.setPosition(sf::Vector2f(origPos.x - objectSprite.getGlobalBounds().width/10, origPos.y - objectSprite.getGlobalBounds().height/10));
        
        objectSprite.setTexture(textureMap["texture1"]);
    }
    else
    {
        objectSprite.setTexture(textureMap["texture2"]);
        objectSprite.setScale(origScale.x, origScale.y);
        objectSprite.setPosition(origPos);
    }
}

void button::interact(){
    std::cout << "Button clicked" << std::endl;
}