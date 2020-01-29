#ifndef _BACKGROUND_HPP
#define _BACKGROUND_HPP

#include "gameObject.hpp"
#include <iostream>
#include <string>

/// \brief
/// A generic implementation of gameObject
/// \details
/// This class is a basic implementation, without any special features, of gameObject. For ease of understanding is the name background kept, as this is its main purpose. 

class background : public gameObject {

public:
    /// \brief
    /// Background contructor
    /// \details
    /// Initializes the inherented gameobject with propper texture, scale, priority, etc.
    background( sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, int objectPriority, std::string textureFile );
};

#endif //_BACKGROUND_HPP