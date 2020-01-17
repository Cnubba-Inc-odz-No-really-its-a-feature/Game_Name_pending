#include "character.hpp"

character::character( sf::Vector2f position, sf::Vector2f scale, std::map<std::string, sf::Texture> textureMap, sf::RenderWindow & window, int prio):
    gameObject(position, scale, textureMap),
    window(window)
{
    priority = prio;
}

void character::setFrame(int max_frame, int row){
        if(counter > 100) {counter = 0; frame++;}
	    if(max_frame < frame) frame = 0;
	    sprite.setTextureRect(sf::IntRect(64*frame, 64*row, 64, 64));
	    counter++;
    }

void character::draw(sf::RenderWindow& window){
    if(!moved){
        setFrame(2,2);
    } 
    moved = false;
    window.draw(sprite);
}

void character::move(sf::Vector2f delta){
    if(delta.x < 0) setFrame(8, 9);
	if(delta.x > 0) setFrame(8, 11);
    sprite.setPosition(sprite.getPosition()+delta);
    if(collision()){
        sprite.setPosition(sprite.getPosition()-delta);
    }
    moved = true;
    //setFrame(2, 2);
}

bool character::collision(){
    if(sprite.getPosition().x <= window.getPosition().x || sprite.getGlobalBounds().width + sprite.getPosition().x >= (window.getPosition().x + window.getSize().x) ){
        return true;
    }
    return false;
}

void character::update(){}
void character::interact(){}