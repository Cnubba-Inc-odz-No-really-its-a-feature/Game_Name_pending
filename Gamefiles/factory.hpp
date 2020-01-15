#ifndef _FACTORY_HPP_
#define _FACTORY_HPP_

#include "objectStorage.hpp"
#include "fstream"
#include "operators.hpp"
#include <map>
#include "testSprite.hpp"
#include "circle.hpp"


class factory{
private:
    std::ifstream inputFile;
    objectStorage &storage;

public:
    factory(objectStorage &storage);
        
    void factorObjectsFromFile(std::string inputFileName);
    std::shared_ptr<gameObject> factorObject(std::ifstream & inputFile);

    void saveState()
    {
        std::cout<< "TODO: not yet implemented, saveState" << std::endl; 
        return;
    }
};


#endif // _FACTORY_HPP_