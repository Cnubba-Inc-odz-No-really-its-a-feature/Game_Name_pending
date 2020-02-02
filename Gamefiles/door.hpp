#ifndef _DOOR_HPP
#define _DOOR_HPP

#include "gameObject.hpp"
#include "memory"
#include "objectStorage.hpp"
#include <SFML/Audio.hpp>
#include <iostream>


/// \brief
/// Implementation of gameObject for the door. This class provides the door you encounter in the dungeon
class door: public gameObject{
private:
    std::vector<gameObject> lootObjectVector;
    int textureFrame = 0;
    int frameCounter = 0;
    bool interacted = false;
    bool alreadyOpen = false;
    objectStorage & storage;
    std::string target;
    std::string returnTarget;
    bool firstrun = true;
    sf::Sound sound;
    sf::SoundBuffer buffer;
    bool animationDone = false;

public:
    /// \brief
    /// Constructor sets all parameters correct for the location and animation
    door(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, objectStorage &storage, int objectPriority, std::string target, std::string soundFile, std::string returnTarget, std::string textureFile, bool opened):
        gameObject(spritePosition, spriteScale, textureMap, firstKey),
        storage(storage), target(target), returnTarget(returnTarget)
    {
        interactable = true;
        gameObject::target = target;
        gameObject::objectPriority = objectPriority;
        gameObject::soundFile = soundFile;
        gameObject::textureFile = textureFile;
        objectSprite.setTextureRect(sf::IntRect(0, 0, 135, 160));
        buffer.loadFromFile(soundFile);
        sound.setBuffer(buffer);
        type = "DOOR_E";
        gameObject::interacted = opened;
        firstrun = !opened;
    }

    /// \brief
    /// Specific implementation for the animation to work correctly
    void setFrame(int maxFrame, int textureRow) override{
        if(frameCounter > 10) {frameCounter = 0; textureFrame++;}
	    objectSprite.setTextureRect(sf::IntRect(133.5*textureFrame, 0*textureRow, 133, 160));
        if(maxFrame < textureFrame) animationDone = true;
	    else frameCounter++;
    }

    /// \brief
    /// First opens the door, then switches to target when interacted with
    void interact() override{
        if(firstrun){
            sound.play();
            firstrun = false;
            gameObject::interacted = true;
        }
        if (textureFrame > 2)storage.setActive(target);
    }
    
    /// \brief
    /// Updates animation and draws the door
    void draw(sf::RenderWindow& gameWindow) override{
        if(gameObject::interacted && !animationDone) setFrame(4, 0);
        if(target == storage.getReturnTarget()){
            gameObject::interacted = true;
            textureFrame = 4;
        } 
        gameWindow.draw(objectSprite);
    }

    /// \brief
    /// Not used
    void move(sf::Vector2f moveDirection) override{}

};

#endif