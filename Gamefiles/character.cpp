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
    if(!moved){
        setFrame(2,2);
    } 
    moved = false;
    gameWindow.draw(objectSprite);
}

void character::move(sf::Vector2f moveDirection){
//    if(delta.x < 0) setFrame(8, 9);
// 	if(delta.x > 0) setFrame(8, 11);
//     sprite.setPosition(sprite.getPosition()+delta);
   if(collision()){
       objectSprite.setPosition(objectSprite.getPosition()-moveDirection);
    }
    moved = true;
    direction = moveDirection;
    //setFrame(2, 2);
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
        objectSprite.setPosition(objectSprite.getPosition()+direction);
    }else{
        setFrame(2,2);
    }

}
void character::interact(){}