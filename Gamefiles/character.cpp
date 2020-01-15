#include "character.hpp"

character::character( sf::Vector2f position, sf::Vector2f scale, std::string spriteTextureName, sf::RenderWindow & window):
    gameObject(position, scale, spriteTextureName),
    window(window)
{}

void character::draw(sf::RenderWindow& window){
    window.draw(sprite);
}

void character::move(sf::Vector2f delta){
    sprite.setPosition(sprite.getPosition()+delta);
    if(collision()){
        sprite.setPosition(sprite.getPosition()-delta);
    }
}

bool character::collision(){
    if(sprite.getPosition().x <= window.getPosition().x || sprite.getGlobalBounds().width + sprite.getPosition().x >= (window.getPosition().x + window.getSize().x) ){
        return true;
    }
    return false;
}

void character::update(){}
void character::interact(){}