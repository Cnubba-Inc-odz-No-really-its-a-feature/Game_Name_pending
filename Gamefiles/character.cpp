#include "character.hpp"

character::character(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, sf::RenderWindow & gameWindow, std::string firstKey, int objectPriority):
    gameObject(spritePosition, spriteScale, textureMap, firstKey),
    gameWindow(gameWindow)
{
    gameObject::objectPriority = objectPriority;
    type = "CHARACTER_E";
}

void character::setFrame(int maxFrame, int textureRow){
        if(frameCounter > 10) {frameCounter = 0; textureFrame++;}
	    if(maxFrame < textureFrame) textureFrame = 0;
	    objectSprite.setTextureRect(sf::IntRect(231*textureFrame + 70, 190*textureRow, 90, 190));
	    frameCounter++;
    }

void character::draw(sf::RenderWindow& gameWindow){

    gameWindow.draw(objectSprite);
}

void character::move(sf::Vector2f moveDirection){

    objectSprite.setPosition(objectSprite.getPosition()+moveDirection);
    if(collision()){
       objectSprite.setPosition(objectSprite.getPosition()-moveDirection);
    }
    moved = true;
    direction = moveDirection;
}

bool character::collision(){
    if(objectSprite.getPosition().x <= 32 || objectSprite.getPosition().x >= 1670 ){
        return true;
    }
    return false;
}

void character::update(){
    if(moved){
        if(direction.x < 0) setFrame(7, 1);
	    if(direction.x > 0) setFrame(7, 2);
        moved = false;
    }else{
        setFrame(5,0);
    }
}

void character::interact(){}