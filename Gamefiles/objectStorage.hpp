#ifndef _OBJECTSTORAGE_HPP_
#define _OBJECTSTORAGE_HPP_

#include <iostream>
#include "memory"
#include "vector"
#include "string"
#include "SFML/Graphics.hpp"
#include "queue"
#include "gameObject.hpp"
#include "objectStorage.hpp"
#include "character.hpp"
#include "fstream"
#include "operators.hpp"
#include "testSprite.hpp"
#include "button.hpp"
#include "titlecard.hpp"
#include "background.hpp"
#include <map>
#include "chest.hpp"
#include "door.hpp"

class objectStorage {
private:
    std::shared_ptr<gameObject> factorObject(std::ifstream & inputFile);
    void factorNewGameState(std::string stateFileName);
    sf::RenderWindow & window;
    void factorMainCharacter();

public:
    bool swappedActive = false;
    std::string tmpActive;
    std::string keyActive = "Title";
    std::map<std::string, std::shared_ptr<std::vector<std::shared_ptr<gameObject>>>> allVectors;

    objectStorage(sf::RenderWindow & window);
    std::shared_ptr<gameObject> character1;
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> & getActive();
    void setActive(std::string newKey);
};

#endif // _OBJECTSTORAGE_HPP_
