#ifndef _DOOR_HPP
#define _DOOR_HPP

#include "gameObject.hpp"
#include "memory"
#include "lootObject.hpp"
#include "objectStorage.hpp"
#
#include <iostream>

class door: public gameObject{
private:
    std::vector<gameObject> lootObjectVector;
    bool open = false;
    int textureFrame = 0;
    int frameCounter = 0;
    bool interacted = false;
    objectStorage & storage;
public:
    door(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, objectStorage &storage, int objectPriority):
        gameObject(spritePosition, spriteScale, textureMap, firstKey),
        storage(storage)
    {
        interactable = true;
        gameObject::objectPriority = objectPriority;
        std::cout << "test" << std::endl;
        objectSprite.setTextureRect(sf::IntRect(0, 0, 135, 160));
    }

    void setFrame(int maxFrame, int textureRow) override{
        if(frameCounter > 10) {frameCounter = 0; textureFrame++;}
	    objectSprite.setTextureRect(sf::IntRect(133.5*textureFrame, 0*textureRow, 133, 160));
        if(maxFrame < textureFrame) interacted = false;
	    else frameCounter++;
    }

    void interact() override{
        std::cout << textureFrame << std::endl;
        if (textureFrame > 2)storage.setActive("Game_1");
        interacted = true;
    }

    void interact(objectStorage& gameStorage, const float& mainCharacterPosition){

    }

    void draw(sf::RenderWindow& gameWindow) override{
        if(interacted) setFrame(4, 0);
        gameWindow.draw(objectSprite);
        if(open){
            for(auto& loot : lootObjectVector){
                loot.draw(gameWindow);
            }
        }
    }

    void move(sf::Vector2f moveDirection) override{}

    void update(){}

};

#endif