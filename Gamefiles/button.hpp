#ifndef _BUTTON_HPP
#define _BUTTON_HPP

#include "gameObject.hpp"
#include "objectStorage.hpp"
#include <iostream>

class button : public gameObject {
private:
    sf::Vector2f origScale;
    sf::Vector2f origPos;
    objectStorage & storage;

public:
    button( sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, int objectPriority, objectStorage & storage );

    void draw(sf::RenderWindow& gameWindow) override;

    void setFrame(int maxFrame, int textureRow);

    void move(sf::Vector2f moveDirection) override;
    void update() override;
    void interact() override;

};


#endif //_CHARACTER_HPP