#ifndef _DOOR_HPP
#define _DOOR_HPP

#include "gameObject.hpp"
#include "memory"
#include "lootObject.hpp"
#include "objectStorage.hpp"
#include <iostream>

class door: public gameObject{
private:
    std::vector<gameObject> lootObjectVector;
    bool open = false;
public:
    door(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, int objectPriority):
        gameObject(spritePosition, spriteScale, textureMap, firstKey)
    {
        interactable = true;
        gameObject::objectPriority = objectPriority;
        std::cout << "test" << std::endl;
        objectSprite.setTextureRect(sf::IntRect(0, 0, 165, 220));
    }

    void interact() override{
           std::cout << "door" << std::endl;
           objectSprite.setTextureRect(sf::IntRect(165, 0, 165, 220));
     
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

    void setFrame(int maxFrame, int textureRow){
    }

};

#endif