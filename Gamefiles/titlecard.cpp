#include "titlecard.hpp"

titlecard::titlecard( sf::Vector2f position, sf::Vector2f scale, std::map<std::string, sf::Texture> textureMap, int prio, objectStorage & storage):
    gameObject(position, scale, textureMap, prio), storage(storage)
{}

void titlecard::draw(sf::RenderWindow& window){
    std::cout << "im being drawn: titlecard" << std::endl;
    window.draw(sprite);
}

void titlecard::move(sf::Vector2f delta){}
void titlecard::update(){
    frameCounter++;
    std::cout << "Framecounter: " << frameCounter << std::endl;
    if (frameCounter < 500){
        return;
    }
    if (frameCounter < 1000){
        sprite.setPosition(sprite.getPosition() + sf::Vector2f(0,-0.2));
    }
    if (frameCounter < 1500){
        return;
    }
    std::cout << sprite.getPosition().x << sprite.getPosition().y;
    storage.setActive("Menu");
    
}
void titlecard::interact(){}