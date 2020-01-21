#include "character.hpp"

character::character(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, sf::RenderWindow & gameWindow, std::string firstKey, int objectPriority):
    gameObject(spritePosition, spriteScale, textureMap, firstKey),
    gameWindow(gameWindow)
{
    gameObject::objectPriority = objectPriority;
}

void character::setFrame(int maxFrame, int textureRow){
        if(frameCounter > 15) {frameCounter = 0; textureFrame++;}
	    if(maxFrame < textureFrame) textureFrame = 0;
	    objectSprite.setTextureRect(sf::IntRect(64*textureFrame, 64*textureRow, 64, 64));
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
    if(objectSprite.getPosition().x <= gameWindow.getPosition().x || objectSprite.getGlobalBounds().width + objectSprite.getPosition().x >= (gameWindow.getPosition().x + gameWindow.getSize().x) ){
        return true;
    }
    return false;
}

void character::update(){
    if(moved){
        if(direction.x < 0) setFrame(8, 9);
	    if(direction.x > 0) setFrame(8, 11);
        moved = false;
    }else{
        setFrame(2,2);
    }
}

void character::interact(){}