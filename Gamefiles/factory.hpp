#ifndef _FACTORY_HPP_
#define _FACTORY_HPP_

#include "gameObject.hpp"
#include "objectStorage.hpp"
#include "fstream"
#include "operators.hpp"
#include "character.hpp"
#include "testSprite.hpp"
#include "button.hpp"
#include "titlecard.hpp"
#include "background.hpp"
#include <map>
#include "chest.hpp"
#include "string"
#include "door.hpp"

class factory{
private:
    

public:
    factory(sf::RenderWindow & window);
    std::shared_ptr<gameObject> factorObject(std::ifstream & inputFile);
    void factorNewGameState(std::string stateFileName);
    void factorMainCharacter();
};


#endif // _FACTORY_HPP_