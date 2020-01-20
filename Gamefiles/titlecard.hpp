#ifndef _TITLECARD_HPP
#define _TITLECARD_HPP

#include "gameObject.hpp"
#include "objectStorage.hpp"
#include "iostream"

class titlecard : public gameObject {
private:
    int frameCounter = 0;
    objectStorage & titleCardStorage;
public:
    titlecard( sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, objectStorage & titleCardStorage, std::string firstKey, int objectPriority);

    void draw(sf::RenderWindow& window) override;

    void setFrame(int maxFrame, int textureRow);

    void move(sf::Vector2f moveDirection) override;
    bool collision();
    void update() override;
    void interact() override;

};
#endif //_TITLECARD_HPP