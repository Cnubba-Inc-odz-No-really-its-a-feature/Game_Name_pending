#include "popup.hpp"

popup::popup(const sf::Vector2f & anker)
: gameObject(spritePosition, spriteScale, textureMap, firstKey, objectPriority) ,anker(anker)
{//select some random cards
}
void popup::interact(){};
void popup::draw(sf::RenderWindow& gameWindow){};
void popup::move(sf::Vector2f moveDirection){};
void popup::update(){};
void popup::setFrame(int maxFrame, int textureRow){};