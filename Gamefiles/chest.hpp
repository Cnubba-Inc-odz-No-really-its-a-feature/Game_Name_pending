#ifndef _CHEST_HPP
#define _CHEST_HPP

#include "gameObject.hpp"
#include "memory"
#include "lootObject.hpp"
#include "objectStorage.hpp"
#include <iostream>
#include <SFML/Audio.hpp>
class chest: public gameObject{
private:
    std::vector<gameObject> lootObjectVector;
    bool open = false;
    int textureFrame = 0;
    int frameCounter = 0;
    bool animationDone = false;
    sf::Sound sound;
    sf::SoundBuffer buffer;
public:

    //bool interacted = false;

    chest(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, int objectPriority, std::string soundFile, std::string textureFile, bool opened):
        gameObject(spritePosition, spriteScale, textureMap, firstKey)
    {
        interactable = true;
        gameObject::objectPriority = objectPriority;
        gameObject::soundFile = soundFile;
        gameObject::textureFile = textureFile;
	    //objectSprite.setTextureRect(sf::IntRect(0, 0, 16, 30));
        objectSprite.setTextureRect(sf::IntRect(0, 0, 47, 35));
        buffer.loadFromFile(soundFile);
        sound.setBuffer(buffer);
        type = "CHEST_E";
        gameObject::interacted = opened;
        open = opened;
        //if(gameObject::interacted) interact();
    }

    void interact() override{
        if(!open){
            sound.play();
            open = true;
            gameObject::interacted = true;
        }
    }

    void interact(objectStorage& gameStorage, const float& mainCharacterPosition){

    }       

    void draw(sf::RenderWindow& gameWindow) override{
        if(gameObject::interacted && !animationDone) setFrame(3, 0);
        gameWindow.draw(objectSprite);
        if(open){
            for(auto& loot : lootObjectVector){
                loot.draw(gameWindow);
            }
        }
    }

    void move(sf::Vector2f moveDirection) override{}

    void update(){}

    void setFrame(int maxFrame, int textureRow) override{
        if(frameCounter > 10) {frameCounter = 0; textureFrame++;}
	    //objectSprite.setTextureRect(sf::IntRect(16*textureFrame, 0*textureRow, 16, 30));
	    objectSprite.setTextureRect(sf::IntRect(47*textureFrame, 0*textureRow, 47, 35));
        if(maxFrame <= textureFrame) animationDone = true;
	    else frameCounter++;
    }

};

#endif