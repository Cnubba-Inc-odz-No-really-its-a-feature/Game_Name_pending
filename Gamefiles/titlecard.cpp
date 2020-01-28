#include "titlecard.hpp"

titlecard::titlecard( sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, objectStorage & titleCardStorage, std::string firstKey, int objectPriority, std::string textureFile):
    gameObject(spritePosition, spriteScale, textureMap, firstKey, objectPriority), 
    titleCardStorage(titleCardStorage)
{
    gameObject::textureFile = textureFile;
    gameObject::objectPriority = objectPriority;
    gameObject::type = "TITLECARD_E";
}

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
    titleCardStorage.setActive("menu.txt");
}

void titlecard::interact(){}
