#ifndef _TESTSPRITE_HPP
#define _TESTSPRITE_HPP
#include "gameObject.hpp"
#include "SFML/Graphics.hpp"

/// \brief
/// A generic implementation of gameObject
/// \details
/// This class is a basic implementation, without any special features, of gameObject. For ease of understanding is the name testsprite kept, as this was its main purpose. 

class textureSprite : public gameObject{


public:

    /// \brief
    /// Background contructor
    /// \details
    /// Initializes the inherented gameobject with propper texture, scale, priority, etc.
    textureSprite(sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, int objectPriority, std::string textureFile):
    gameObject(spritePosition, spriteScale, textureMap, firstKey)
    {
        gameObject::textureFile = textureFile;
        gameObject::objectPriority = objectPriority;
        type = "TESTSPRITE_E";  
    }
};

#endif