#ifndef _GAMEOBJECT_HPP
#define _GAMEOBJECT_HPP

#include "string"
#include "iostream"
#include "memory"
#include <SFML/Graphics.hpp>
#include <string>

/// \brief
/// Main game object class, superclass for most everything thats drawn
/// \details
/// Nearly all drawable all derived from this class. It has a couple of functions that get called every frame, like update and draw
/// To easely make new object you can add lines to the txt files, the program wil automaticly generate the correct objects and save them in the correct state
/// \todo
/// This class currently holds to much vars and overlapping functions that are not all still needed and needs to be refactored to check for unused items


class gameObject{
protected:
    std::string objectID;
    int objectTypeID;
    sf::Sprite objectSprite;
    sf::Texture spriteTexture;
    std::map<std::string, sf::Texture> textureMap;
    bool interactable = false;
    friend class lootObject;
    std::string type;

    /// \brief
    /// private function thats a thin wrapper to check if the mouse hovers over this object. 
    bool isHovering(){
        return objectSprite.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
    }

public:

    /// \brief
    /// default constructor of gameobject. Needs to be call at construction of derived classes
    /// \details
    /// Saves all nessasery objects and variables used for drawing and texturing the sprite in the correct way/order. 
    /// The texture map was planned to be used to allow multiple textures to be switched between, but is really only usefull in the derived class button
    /// since we use setsubrect for the anamations.
    gameObject(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, int objectPriority =0): 
        textureMap(textureMap),
        objectPriority(objectPriority)
    {
        firstkey = firstKey;
        objectSprite.setPosition(spritePosition);
        objectSprite.setScale(spriteScale.x, spriteScale.y);
        spriteTexture = textureMap[firstKey];
        objectSprite.setTexture(spriteTexture);
        objectID = 5;
    }

    gameObject(){};



    std::string soundFile;
    std::string textureFile;
    std::string firstkey;
    std::string secondkey;
    std::string target;
    bool interacted = false;
    int objectPriority;

    /// \brief
    /// returns wheter the object can interact
    bool isInteractable(){ return interactable; }
    sf::Sprite getSprite(){ return objectSprite; }

    /// \brief
    /// Returns type of object, this feature is not really used or standardised in any way
    std::string getObjectID(){ return objectID; }

    /// \brief
    /// Returns type of object, this feature is not really used or standardised in any way
    std::string getType(){ return type; }

    /// \brief
    /// gets called if a object is interacable and the user interacts with it.
    virtual void interact(){};
    
    /// \brief
    /// default implementation of draw, since most objects just need their sprite drawn.
    virtual void draw(sf::RenderWindow& gameWindow){
        gameWindow.draw(objectSprite);
    }

    /// \brief
    /// Set a new target for the object to state switch to.
    virtual void setTarget(std::string newTarget){};

    /// \brief
    /// moves the location of the sprite by a given delta.
    virtual void move(sf::Vector2f moveDirection){};

    /// \brief
    /// Jump to a new aboslute location.
    virtual void jumpLocationTo(sf::Vector2f jumpLocation){};

    /// \brief
    /// Gets called every frame that the object is in the active array
    virtual void update(){};

    /// \brief
    /// function to set the correct frame of the animation
    virtual void setFrame(int maxFrame, int textureRow){};
};

#endif