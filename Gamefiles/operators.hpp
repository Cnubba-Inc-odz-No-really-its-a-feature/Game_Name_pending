#include "exeptions.hpp"
#include <SFML/Graphics.hpp>
#include "fstream"

#ifndef OPERATORS_HPP
#define OPERATORS_HPP

std::ifstream &operator>>(std::ifstream &input, sf::Vector2f &rhs);
std::ifstream &operator>>(std::ifstream &input, sf::Color &rhs);

#endif //OPERATORS_HPP
