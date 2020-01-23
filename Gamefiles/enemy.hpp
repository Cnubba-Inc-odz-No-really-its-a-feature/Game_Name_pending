#ifndef _ENEMY_HPP
#define _ENEMY_HPP

#include "gameObject.hpp"
#include "memory"
#include "lootObject.hpp"
#include "objectStorage.hpp"
#include <iostream>

class enemy: public gameObject{
private:
    std::vector<gameObject> lootObjectVector;
    bool open = false;
    int textureFrame = 0;
    int frameCounter = 0;
    bool interacted = false;
    objectStorage & storage;
    std::string target;

public:
    enemy(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, objectStorage &storage, int objectPriority, std::string target):
        gameObject(spritePosition, spriteScale, textureMap, firstKey),
        storage(storage), target(target)
    {
        interactable = true;
        gameObject::objectPriority = objectPriority;
        objectSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    }

    void setFrame(int maxFrame, int textureRow) override{}

    void interact() override{
        storage.setActive(target);
    }

    void interact(objectStorage& gameStorage, const float& mainCharacterPosition){

    }

    void draw(sf::RenderWindow& gameWindow) override{
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