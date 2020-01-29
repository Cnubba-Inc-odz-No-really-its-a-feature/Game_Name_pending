#ifndef _BACKGROUND_HPP
#define _BACKGROUND_HPP

#include "gameObject.hpp"
#include <iostream>
#include <string>

class background : public gameObject {

public:

    background( sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, int objectPriority, std::string textureFile );

    void draw(sf::RenderWindow& gameWindow) override;
    void setFrame(int maxFrame, int textureRow);

    void move(sf::Vector2f moveDirection) override;
    void update() override;
    void interact() override;

};

#endif //_BACKGROUND_HPP