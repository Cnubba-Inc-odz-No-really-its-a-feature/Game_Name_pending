#include "character.hpp"

character::character( sf::Vector2f position, sf::Vector2f scale, std::map<std::string, sf::Texture> textureMap, sf::RenderWindow & window, int prio):
    gameObject(position, scale, textureMap),
    window(window)
{
    priority = prio;
}

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