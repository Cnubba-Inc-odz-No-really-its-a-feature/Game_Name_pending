#include "objectStorage.hpp"

std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> objectStorage::getActive(){
        return allVectors[keyActive];
    }

void objectStorage::setActive(std::string newKey){
    keyActive = newKey;
}

objectStorage::objectStorage():
    menu(new std::vector<std::shared_ptr<gameObject>>), 
    game(new std::vector<std::shared_ptr<gameObject>>), 
    title(new std::vector<std::shared_ptr<gameObject>>)
{
    allVectors.insert({"Menu", menu});
    allVectors.insert({"Game", game});
    allVectors.insert({"Title", title});
}