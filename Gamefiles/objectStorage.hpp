#ifndef _OBJECTSTORAGE_HPP_
#define _OBJECTSTORAGE_HPP_

class factory{
private:
    std::ifstream inputFile;
    objectStorage &storage;
    sf::RenderWindow & window;

public:
    factory(objectStorage &storage, sf::RenderWindow & window);
    std::shared_ptr<gameObject> factorObject(std::ifstream & inputFile);
    void factorNewGameState(std::string stateFileName);
    void factorMainCharacter();
};

#include "vector"
#include "memory"
#include "queue"
#include "gameObject.hpp"
#include "string"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "character.hpp"

class objectStorage {
public:
    bool swappedActive = false;
    std::string tmpActive;
    std::string keyActive = "Title";
    std::map<std::string, std::shared_ptr<std::vector<std::shared_ptr<gameObject>>>> allVectors;

    objectStorage();
    std::shared_ptr<gameObject> character1;
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> & getActive();
    void setActive(std::string newKey);
};

#endif // _OBJECTSTORAGE_HPP_
