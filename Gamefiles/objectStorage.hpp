#ifndef _OBJECTSTORAGE_HPP_
#define _OBJECTSTORAGE_HPP_

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
    std::string keyActive = "Title";
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> menu;
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> game;
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> title;
    std::map<std::string, std::shared_ptr<sf::Texture>> textureMap;
    std::map<std::string, std::shared_ptr<std::vector<std::shared_ptr<gameObject>>>> allVectors;

    objectStorage();
    std::shared_ptr<gameObject> character1;
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> getActive();

    void setActive(std::string key);
};

#endif // _OBJECTSTORAGE_HPP_
