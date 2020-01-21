#include "titlecard.hpp"

titlecard::titlecard( sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, objectStorage & titleCardStorage, std::string firstKey, int objectPriority):
    gameObject(spritePosition, spriteScale, textureMap, firstKey, objectPriority), 
    titleCardStorage(titleCardStorage)
{}

void titlecard::draw(sf::RenderWindow& gameWindow){
    gameWindow.draw(objectSprite);
}

void titlecard::setFrame(int maxFrame, int textureRow){}

void titlecard::move(sf::Vector2f Miretion){}

void titlecard::update(){
    frameCounter++;
    if (frameCounter < 5){
        return;
    }
    if (frameCounter < 100){
        objectSprite.setPosition(objectSprite.getPosition() + sf::Vector2f(0,-0.2));
    }
    if (frameCounter < 150){
        return;
    }
    titleCardStorage.setActive("Menu");
}

void titlecard::interact(){}
