#ifndef _FACTORY_HPP_
#define _FACTORY_HPP_

#include "gameObject.hpp"
#include "objectStorage.hpp"
#include "fstream"

class factory{
private:
    std::ifstream inputFile;
    objectStorage &storage;

public:
    factory(objectStorage &storage): storage(storage){
        //generate all objects and add them to the storage
        inputFile.open("source.txt");
        
    };
};


#endif // _FACTORY_HPP_