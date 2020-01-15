#include "operators.hpp"

std::ifstream &operator>>(std::ifstream &input, sf::Vector2f &rhs) {
  char c;
  if (!(input >> c)) {
    throw end_of_file("end_of_file");
  }
  if (!(input >> rhs.x)) {
    throw unknown_pos(c);
  }
  if (!(input >> c)) {
    throw unknown_pos(c);
  }
  if (!(input >> rhs.y)) {
    throw unknown_pos(c);
  }
  if (!(input >> c)) {
    throw unknown_pos(c);
  }
  if (c != ')') {
    throw unknown_pos(c);
  }
  return input;
}

std::ifstream &operator>>(std::ifstream &input, sf::Color &rhs) {
  std::string color;
  input >> color;
  if ("Black" == color) {
    rhs = sf::Color::Black;
  } else if ("White" == color) {
    rhs = sf::Color::White;
  } else if ("Red" == color) {
    rhs = sf::Color::Red;
  } else if ("Green" == color) {
    rhs = sf::Color::Green;
  } else if ("Blue" == color) {
    rhs = sf::Color::Blue;
  } else if ("Yellow" == color) {
    rhs = sf::Color::Yellow;
  } else if ("Magenta" == color) {
    rhs = sf::Color::Magenta;
  } else if ("Cyan" == color) {
    rhs = sf::Color::Cyan;
  } else if ("Transparent" == color) {
    rhs = sf::Color::Transparent;
  } else {
    throw unknown_color(color.c_str());
  }
  return input;
}

bool operator<(const gameObject& lhs, const gameObject& rhs){
        return lhs.priority < rhs.priority;
    } 