#ifndef _BUTTON_HPP
#define _BUTTON_HPP

#include "gameObject.hpp"
#include "objectStorage.hpp"
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>

class button : public gameObject {
private:
    sf::Vector2f origScale;
    sf::Vector2f origPos;
    objectStorage & storage;
    std::string target;

    bool firstrun = true;
    sf::Sound sound;
    sf::SoundBuffer buffer;

public:
    button( sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, objectStorage & storage, int objectPriority, std::string target, std::string soundFile);

    void draw(sf::RenderWindow& gameWindow) override;

    void setFrame(int maxFrame, int textureRow);

    void setTarget(std::string newTarget) override;

    void move(sf::Vector2f moveDirection) override;
    void update() override;
    void interact() override;

};


#endif //_CHARACTER_HPP