#ifndef _CHEST_HPP
#define _CHEST_HPP

#include "popup.hpp"
#include "gameObject.hpp"
#include "memory"
#include "lootObject.hpp"
#include "objectStorage.hpp"
#include <iostream>
#include <SFML/Audio.hpp>

///\brief 
/// chest implementation of gameobject
///\details
/// when interacted with, opens and displays 3 cards to pick from. when choosen the card will be added to the deck.
/// also can be found in the rewardroom, when the card is then picked the player will be brought back to the returntarget
///\todo
/// currently it uses its draw prioity to determen if a rare or normal card should be displayed. this is ugly

class chest: public gameObject{
private:
    std::vector<gameObject> lootObjectVector;
    bool open = false;
    int textureFrame = 0;
    int frameCounter = 0;
    bool animationDone = false;
    //bool interacted = false;
    bool avalable = true;
    popup itemPopup; 
    objectStorage & storage;
    sf::Sound sound;
    sf::SoundBuffer buffer;
     int objectPriority;

public:
    /// \brief
    /// Constructor sets all parameters correct for the location and animation
    chest(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, int objectPriority, objectStorage & storage, std::string soundFile, std::string textureFile, bool opened):
        gameObject(spritePosition, spriteScale, textureMap, firstKey), itemPopup(spritePosition, "gameAssets/popupBackground.png", objectPriority), storage(storage), objectPriority(objectPriority)
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

    /// \brief
    /// if not yet opened it will play its open animation 
    void interact() override{
        if(!open){
            sound.play();
            open = true;
            gameObject::interacted = true;
            // itemPopup.interact();
        }
    }

    /// \brief
    /// No longer used or implemented
    void interact(objectStorage& gameStorage, const float& mainCharacterPosition){

    }       

    /// \brief
    /// Draws the chest in the correct phase of animation and draws the popup if nessesary
    void draw(sf::RenderWindow& gameWindow) override{
        if(gameObject::interacted && !animationDone) setFrame(3, 0);
        gameWindow.draw(objectSprite);

        if(open && avalable){
            itemPopup.draw(gameWindow);
        }

        // if(open){
        //     for(auto& loot : lootObjectVector){
        //         loot.draw(gameWindow);
        //     }
        // }
    }

    void move(sf::Vector2f moveDirection) override{}

    /// \brief
    /// checks if a card was choosen, if so, add the card to the deck and if nesessery switch state
    void update(){
        if(avalable){
            int chosen = itemPopup.update();
            if (chosen != -1)
            {
                avalable = false;
                storage.deckEditor.newOwnCard(chosen);
                if (objectPriority == 5)
                {
                    storage.setActive(storage.getReturnTarget());
                }
                
            }
            
        }
    }
    
    
    ///\brief
    /// updates to the correct frame of the animation
    void setFrame(int maxFrame, int textureRow) override{
        if(frameCounter > 10) {frameCounter = 0; textureFrame++;}
	    objectSprite.setTextureRect(sf::IntRect(47*textureFrame, 0*textureRow, 47, 35));
        if(maxFrame <= textureFrame) animationDone = true;
	    else frameCounter++;
    }

};

#endif