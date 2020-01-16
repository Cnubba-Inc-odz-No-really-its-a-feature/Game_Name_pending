#ifndef _FACTORY_HPP_
#define _FACTORY_HPP_

#include "gameObject.hpp"
#include "objectStorage.hpp"
#include "fstream"
#include "operators.hpp"
#include "character.hpp"
#include <map>

class factory{
private:
    std::ifstream inputFile;
    objectStorage &storage;
    sf::RenderWindow & window;
public:
    factory(objectStorage &storage, sf::RenderWindow & window);
    std::shared_ptr<gameObject> factorObject(std::ifstream & inputFile);
    void factorObjectsFromFile(std::string inputFileName);
    void saveState();
};


#endif // _FACTORY_HPP_