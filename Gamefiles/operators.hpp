#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include "exeptions.hpp"
#include <SFML/Graphics.hpp>
#include "fstream"
#include "gameObject.hpp"
#include <map>

///\brief
/// All the object types we have in an enum
enum objectTypes_E{TESTSPRITE_E, CIRCLE_E, CHARACTER_E, CHEST_E, DOOR_E , BUTTON_E, BACKGROUND_E, TITLECARD_E, ENEMY_E, NEWGAMEBUTTON_E};

///\brief
/// Not used anymore
enum storageSpecifier_E{STORAGEM_E, STORAGEG_E};

///\brief
/// >> operator that interperts the texture into the objectTexture
std::ifstream &operator>>(std::ifstream &input, sf::Texture &objectTexture);

///\brief
/// >> operator that interperts the type into the objectType
std::ifstream &operator>>(std::ifstream &input, objectTypes_E& objectType);

///\brief
/// >> operator that interperts the location into the rhs
std::ifstream &operator>>(std::ifstream &input, sf::Vector2f &rhs);

///\brief
/// >> operator that interperts the color into the rhs
std::ifstream &operator>>(std::ifstream &input, sf::Color &rhs);

///\brief
/// nesessery operator for finding the higher priority gameobject
bool operator<(const gameObject& lhs, const gameObject& rhs);

#endif //OPERATORS_HPP
