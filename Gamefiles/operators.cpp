#include "operators.hpp"




std::ifstream& operator>>(std::ifstream &input, objectTypes_E &objectType){
  std::string typeString;
  input>>typeString;
  if(typeString == "objectTypes_E::TESTSPRITE_E"){
    objectType = objectTypes_E::TESTSPRITE_E;
  }else if(typeString == "objectTypes_E::CIRCLE_E"){
    objectType = objectTypes_E::CIRCLE_E;
  }else if(typeString == "objectTypes_E::CHARACTER_E"){
    objectType = objectTypes_E::CHARACTER_E;
  }else if(typeString == "objectTypes_E::CHEST_E"){
    objectType = objectTypes_E::CHEST_E;
  }else if(typeString == "objectTypes_E::DOOR_E"){
    objectType = objectTypes_E::DOOR_E;
  }else if(typeString == "objectTypes_E::ENEMY_E"){
    objectType = objectTypes_E::ENEMY_E;
  }else if(typeString == "objectTypes_E::BUTTON_E"){
    objectType = objectTypes_E::BUTTON_E;
  }else if(typeString == "objectTypes_E::TITLECARD_E"){
    objectType = objectTypes_E::TITLECARD_E;
  }else if(typeString == "objectTypes_E::BACKGROUND_E"){
    objectType = objectTypes_E::BACKGROUND_E;
  }else if(typeString == "objectTypes_E::NEWGAMEBUTTON_E"){
    objectType = objectTypes_E::NEWGAMEBUTTON_E;
  }else{
    throw invalid_type("invalid Type string Found");
  }
  return input;
}




std::ifstream &operator>>(std::ifstream &input, sf::Vector2f &rhs) {
  char c;
  if (!(input >> c)) {
    throw end_of_file("end_of_file");
  }
  if (! (c == '(')){
    throw unknown_pos(c);
  }
  if (!(input >> rhs.x)) {
    throw unknown_pos('X');
  }
  if (!(input >> c)) {
    throw unknown_pos(c);
  }
  if (! (c == ',')){
    throw unknown_pos(c);
  }
  if (!(input >> rhs.y)) {
    throw unknown_pos('y');
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
        return lhs.objectPriority < rhs.objectPriority;
} 