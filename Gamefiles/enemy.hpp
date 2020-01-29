#ifndef _ENEMY_HPP
#define _ENEMY_HPP

#include "gameObject.hpp"
#include "memory"
#include "lootObject.hpp"
#include "objectStorage.hpp"
#include <iostream>

class enemy: public gameObject{
private:
    int textureFrame = 0;
    int frameCounter = 0;
    objectStorage & storage;
    std::string target;

public:

    //bool interacted = false;

    enemy(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, objectStorage &storage, int objectPriority, std::string target, std::string textureFile, bool interact):
        gameObject(spritePosition, spriteScale, textureMap, firstKey),
        storage(storage), target(target)
    {
        interactable = true;
        gameObject::target = target;
        gameObject::textureFile = textureFile;
        gameObject::objectPriority = objectPriority;
        objectSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
        type = "ENEMY_E";
        gameObject::interacted = interact;
    }

    void setFrame(int maxFrame, int textureRow) override{
        if(frameCounter > 10) {frameCounter = 0; textureFrame++;}
	    if(maxFrame < textureFrame) textureFrame = 0;
	    objectSprite.setTextureRect(sf::IntRect(64*textureFrame, 64*textureRow, 64, 64));
	    frameCounter++;
    }

    void interact() override{
        if(!gameObject::interacted){
            storage.setActive(target);
            gameObject::interacted = true;
        }
    }

    void interact(objectStorage& gameStorage, const float& mainCharacterPosition){

    }

    void draw(sf::RenderWindow& gameWindow) override{
        setFrame(2,2);
        gameWindow.draw(objectSprite);
    }

    void move(sf::Vector2f moveDirection) override{}

    void update(){}

};

#endif