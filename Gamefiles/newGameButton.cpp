#include "newGameButton.hpp"
#include <iostream>


newGameButton::newGameButton(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, objectStorage &storage,  int objectPriority, std::string target, std::string soundFile, std::string textureFile):
    gameObject(spritePosition, spriteScale, textureMap, firstKey, objectPriority), 
    origScale(spriteScale), 
    origPos(spritePosition),
    storage(storage),
    target(target)
{
    interactable = true; objectTypeID = 100;
    buffer.loadFromFile(soundFile);
    sound.setBuffer(buffer);
    type = "BUTTON_E";
    gameObject::textureFile = textureFile;
    gameObject::secondkey = "texture2";
}

void newGameButton::draw(sf::RenderWindow& gameWindow){
    gameWindow.draw(objectSprite);
}

void newGameButton::setFrame(int maxFrame, int textureRow  ){}

void newGameButton::move(sf::Vector2f moveDirection){}

void newGameButton::setTarget(std::string newTarget){
    target = newTarget;
}

void newGameButton::update(){
    if (isHovering()){
        objectSprite.setScale(origScale.x * 1.2, origScale.y * 1.2);
        objectSprite.setPosition(sf::Vector2f(origPos.x - objectSprite.getGlobalBounds().width/10, origPos.y - objectSprite.getGlobalBounds().height/10));
        objectSprite.setTexture(textureMap[secondkey]);
    }else{
        objectSprite.setTexture(textureMap[firstkey]);
        objectSprite.setScale(origScale.x, origScale.y);
        objectSprite.setPosition(origPos);
    }
}

void newGameButton::deleteSaves(){
    remove( "room1Save.txt" );
    remove( "room2Save.txt" );
    remove( "room3Save.txt" );
    remove( "room4Save.txt" );
    remove( "room5Save.txt" );
    remove( "room6Save.txt" );
    remove( "room7Save.txt" );
    remove( "room8Save.txt" );
}

void newGameButton::interact(){
    deleteSaves();
    storage.setActive(target);
    if(firstrun){
        sound.play();
        firstrun = false;
    }
}