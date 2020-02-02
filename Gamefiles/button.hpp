#ifndef _BUTTON_HPP
#define _BUTTON_HPP

#include "gameObject.hpp"
#include "objectStorage.hpp"
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>


/// \brief
/// The button class, has a hover animation and switches state to target when pressed
class button : public gameObject {
private:
    /// \brief
    /// Scale at the moment of construction. 
    sf::Vector2f origScale;
    /// \brief
    /// Pos at the moment of construction
    sf::Vector2f origPos;
    /// \brief
    /// Saves storage for setActive
    objectStorage & storage;
    /// \brief
    /// Saves target for setActive
    std::string target;
    /// \brief
    /// 
    sf::Sound sound;
    sf::SoundBuffer buffer;

public:

    /// \brief
    /// Button constructor.
    /// \details
    /// Initializes the inherented gameobject with propper texture, scale, priority, etc and saves what it needs itself
    button( sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, objectStorage & storage, int objectPriority, std::string target, std::string soundFile, std::string textureFile);

    
    void draw(sf::RenderWindow& gameWindow) override;

    void setFrame(int maxFrame, int textureRow);

    void setTarget(std::string newTarget) override;

    void move(sf::Vector2f moveDirection) override;
    void update() override;
    void interact() override;

};


#endif //_CHARACTER_HPP