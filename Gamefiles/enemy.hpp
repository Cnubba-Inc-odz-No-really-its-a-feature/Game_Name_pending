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
    int textureSheetTiles;
    sf::Vector2f textureFrameBounds;
    int tileSize;

public:

    //bool interacted = false;

    enemy(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, objectStorage &storage, int objectPriority, std::string target, std::string textureFile, bool interact, int textureSheetTiles):
        gameObject(spritePosition, spriteScale, textureMap, firstKey),
        storage(storage), target(target), textureSheetTiles(textureSheetTiles)
    {
        interactable = true;
        gameObject::target = target;
        gameObject::textureFile = textureFile;
        gameObject::objectPriority = objectPriority;
        type = "ENEMY_E";
        gameObject::interacted = interact;
        textureFrameBounds = sf::Vector2f(objectSprite.getLocalBounds().width / textureSheetTiles, objectSprite.getLocalBounds().height) ;
        setFrame(textureSheetTiles-1,0);
    }

    void setFrame(int maxFrame, int textureRow) override{
        if(frameCounter > 10) {frameCounter = 0; textureFrame++;}
	    if(maxFrame < textureFrame) textureFrame = 0;
	    objectSprite.setTextureRect(sf::IntRect((textureFrameBounds.x*textureFrame)+47, (textureFrameBounds.y*textureRow)-10, textureFrameBounds.x - 97, textureFrameBounds.y));
	    objectSprite.setOrigin(sf::Vector2f(objectSprite.getLocalBounds().width/2, 0));
        frameCounter++;
        std::cout<<textureSheetTiles <<std::endl;
    }

    void interact() override{
        if(!gameObject::interacted){
            storage.setActive(target);
            gameObject::interacted = true;
        }
    }

    void draw(sf::RenderWindow& gameWindow) override{
        setFrame(textureSheetTiles-1,0);
        gameWindow.draw(objectSprite);

    }

    void update(){
        if(storage.character1->getSprite().getGlobalBounds().intersects(objectSprite.getGlobalBounds()) && not gameObject::interacted){
            storage.setActive("cardgame.txt", gameObject::textureFile);
            gameObject::interacted = true;
            storage.enemyTex = gameObject::textureFile;
            std::cout<<gameObject::textureFile<<std::endl;
            storage.enemyTexTextureSheetTiles = textureSheetTiles;
        }
    }

};

#endif