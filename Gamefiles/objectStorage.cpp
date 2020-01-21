#include "objectStorage.hpp"

std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> & objectStorage::getActive(){
        return allVectors[keyActive];
    }

void objectStorage::setActive(std::string newKey){
    swappedActive = true;
    tmpActive = newKey;
    if(allVectors.count(newKey) == 0)
    {
        
    }
    
}

objectStorage::objectStorage()
{
}