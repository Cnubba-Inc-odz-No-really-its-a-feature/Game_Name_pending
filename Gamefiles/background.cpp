#include "background.hpp"

background::background( sf::Vector2f spritePosition, sf::Vector2f spriteScale, std::map<std::string, sf::Texture> textureMap, std::string firstKey, int objectPriority, std::string textureFile):
    gameObject(spritePosition, spriteScale, textureMap, firstKey, objectPriority)
{
    gameObject::textureFile = textureFile;
    gameObject::objectPriority = objectPriority;
    type = "BACKGROUND_E";
    sf::Text();
}

