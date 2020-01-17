#include "character.hpp"

character::character( sf::Vector2f position, sf::Vector2f scale, std::map<std::string, sf::Texture> textureMap, sf::RenderWindow & window, int prio):
    gameObject(position, scale, textureMap),
    window(window)
{
    priority = prio;
}

void character::setFrame(int max_frame){
        if(counter > 10) {counter = 0; frame++;}
	    if(max_frame < frame) frame = 0;
	    sprite.setTextureRect(sf::IntRect(64*frame, 64*2, 64, 64));
	    counter++;
    }

void character::draw(sf::RenderWindow& window){
    window.draw(sprite);
}

void character::move(sf::Vector2f delta){
    sprite.setPosition(sprite.getPosition()+delta);
    if(collision()){
        sprite.setPosition(sprite.getPosition()-delta);
    }
    setFrame(2);
}

bool character::collision(){
    if(sprite.getPosition().x <= window.getPosition().x || sprite.getGlobalBounds().width + sprite.getPosition().x >= (window.getPosition().x + window.getSize().x) ){
        return true;
    }
    return false;
}

void character::update(){}
void character::interact(){}