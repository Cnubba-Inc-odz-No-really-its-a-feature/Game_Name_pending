#ifndef _CHARACTER_HPP
#define _CHARACTER_HPP

#include "gameObject.hpp"
#include <iostream>

class character : public gameObject {
private:
    sf::RenderWindow & window;
public:
    character( sf::Vector2f position, sf::Vector2f scale, std::map<std::string, sf::Texture> textureMap, sf::RenderWindow & window, int prio );

    bool collision();
    void draw(sf::RenderWindow& window) override;
    void move(sf::Vector2f delta) override;
    void update() override;
    void interact() override;

};



#endif //_CHARACTER_HPP