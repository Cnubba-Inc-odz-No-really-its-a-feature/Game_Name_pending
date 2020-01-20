#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include "exeptions.hpp"
#include <SFML/Graphics.hpp>
#include "fstream"
#include "gameObject.hpp"
#include <map>


enum objectTypes_E{TESTSPRITE_E, CIRCLE_E, CHARACTER_E, CHEST_E, BUTTON_E, BACKGROUND_E, TITLECARD_E};
enum storageSpecifier_E{STORAGEM_E, STORAGEG_E};

std::ifstream &operator>>(std::ifstream &input, sf::Texture &objectTexture);
std::ifstream &operator>>(std::ifstream &input, objectTypes_E& objectType);
std::ifstream &operator>>(std::ifstream &input, sf::Vector2f &rhs);
std::ifstream &operator>>(std::ifstream &input, sf::Color &rhs);
bool operator<(const gameObject& lhs, const gameObject& rhs);

#endif //OPERATORS_HPP
