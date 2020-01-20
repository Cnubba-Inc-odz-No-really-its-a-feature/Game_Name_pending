#ifndef _CHARACTER_HPP
#define _CHARACTER_HPP

#include "gameObject.hpp"
#include <iostream>
#include <string>

class character : public gameObject {
private:
    sf::RenderWindow & gameWindow;
    int textureFrame = 0;
    int frameCounter = 0;
    bool moved = false;
    sf::Vector2f direction = sf::Vector2f(0,0);
public:
    character(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, sf::RenderWindow & gameWindow, std::string firstKey, int objectPriority);

    void draw(sf::RenderWindow& gameWindow) override;

    void move(sf::Vector2f moveDirection) override;
    bool collision();
    void update() override;
    void interact() override;
    void setFrame(int maxFrame, int textureRow) override;

};



#endif 