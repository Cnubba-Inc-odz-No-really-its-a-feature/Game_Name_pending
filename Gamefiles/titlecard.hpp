#ifndef _TITLECARD_HPP
#define _TITLECARD_HPP

#include "gameObject.hpp"
#include "objectStorage.hpp"
#include "iostream"

class titlecard : public gameObject {
private:
    int frameCounter = 0;
    objectStorage & storage;
public:
    titlecard( sf::Vector2f position, sf::Vector2f scale, std::map<std::string, sf::Texture> textureMap, int prio, objectStorage & storage );

    void draw(sf::RenderWindow& window) override;

    void setFrame(int max_frame, int row);

    void move(sf::Vector2f delta) override;
    bool collision();
    void update() override;
    void interact() override;

};
#endif //_TITLECARD_HPP