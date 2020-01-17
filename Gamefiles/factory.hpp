#ifndef _FACTORY_HPP_
#define _FACTORY_HPP_

#include "gameObject.hpp"
#include "objectStorage.hpp"
#include "fstream"
#include "operators.hpp"
#include "character.hpp"
#include "testSprite.hpp"
#include <map>
#include "chest.hpp"
#include "string"

class factory{
private:
    std::ifstream inputFile;
    objectStorage &storage;
    sf::RenderWindow & window;
public:
    factory(objectStorage &storage, sf::RenderWindow & window): 
        storage(storage),
        window(window)
    {}

std::shared_ptr<gameObject> factorObject(std::ifstream & inputFile);

void factorNewGameState(std::string stateFileName);
void factorMainCharacter();

    void saveState()
    {
        std::cout<< "TODO: not yet implemented, saveState" << std::endl; 
        return;
    };
};


#endif // _FACTORY_HPP_