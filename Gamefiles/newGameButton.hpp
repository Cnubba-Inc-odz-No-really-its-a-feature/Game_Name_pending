#ifndef _NEWGAMEBUTTON_HPP
#define _NEWGAMEBUTTON_HPP

#include "gameObject.hpp"
#include "objectStorage.hpp"
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>

class newGameButton : public gameObject {
private:
    sf::Vector2f origScale;
    sf::Vector2f origPos;
    objectStorage & storage;
    std::string target;

    bool firstrun = true;
    sf::Sound sound;
    sf::SoundBuffer buffer;

public:


    newGameButton( sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, objectStorage & storage, int objectPriority, std::string target, std::string soundFile, std::string textureFile);

    void deleteSaves();

    void draw(sf::RenderWindow& gameWindow) override;

    void setFrame(int maxFrame, int textureRow);

    void setTarget(std::string newTarget) override;

    void move(sf::Vector2f moveDirection) override;
    void update() override;
    void interact() override;

};


#endif //_NEWGAMEBUTTON_HPP