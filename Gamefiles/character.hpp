#ifndef _CHARACTER_HPP
#define _CHARACTER_HPP

#include "gameObject.hpp"
#include <iostream>

class character : public gameObject {
private:
    sf::RenderWindow & window;
    int frame = 0;
    int counter = 0;
    bool moved = false;
public:
    character( sf::Vector2f position, sf::Vector2f scale, std::map<std::string, sf::Texture> textureMap, sf::RenderWindow & window, int prio );

    void draw(sf::RenderWindow& window) override;

    void move(sf::Vector2f delta) override;
    bool collision();
    void update() override;
    void interact() override;
    void setFrame(int max_frame, int row) override;

};



#endif 