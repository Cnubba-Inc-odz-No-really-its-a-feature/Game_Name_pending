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
        setFrame(2,2);
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

    void draw(sf::RenderWindow& gameWindow) override{
        gameWindow.draw(objectSprite);
    }

    void update(){
        if(storage.character1->getSprite().getGlobalBounds().intersects(objectSprite.getGlobalBounds()) && not gameObject::interacted){
            storage.setActive("cardgame.txt", gameObject::textureFile);
            gameObject::interacted = true;
        }
    }

};

#endif