#ifndef _OBJECTSTORAGE_HPP_
#define _OBJECTSTORAGE_HPP_

#include "vector"
#include "memory"
#include "queue"
#include "gameObject.hpp"
#include "string"
#include "SFML/Graphics.hpp"
#include <iostream>

class objectStorage {
private:
    std::string keyActive = "Menu";
    

public:
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> menu;
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> game;
    std::map<std::string, std::shared_ptr<std::vector<std::shared_ptr<gameObject>>>> allVectors;

    objectStorage():menu(new std::vector<std::shared_ptr<gameObject>>), game(new std::vector<std::shared_ptr<gameObject>>){
        allVectors.insert({"Menu", menu});
        allVectors.insert({"Game", game});
        std::cout<<"object storage is created" << std::endl;
    }
    std::shared_ptr<gameObject> character;
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> getActive(){
        return allVectors[keyActive];
    }

    void setActive(std::string key){
        keyActive = key;
    }
};

#endif // _OBJECTSTORAGE_HPP_
