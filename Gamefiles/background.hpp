#ifndef _BACKGROUND_HPP
#define _BACKGROUND_HPP

#include "gameObject.hpp"
#include <iostream>

class background : public gameObject {

public:
    background( sf::Vector2f position, sf::Vector2f scale, std::map<std::string, sf::Texture> textureMap, int prio );

    void draw(sf::RenderWindow& window) override;
    void setFrame(int max_frame, int row);

    void move(sf::Vector2f delta) override;
    void update() override;
    void interact() override;

};

#endif //_BACKGROUND_HPP