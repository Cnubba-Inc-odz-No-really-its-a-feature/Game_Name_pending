#ifndef _CHEST_HPP
#define _CHEST_HPP

#include "gameObject.hpp"
#include "memory"
#include <iostream>

class chest: gameObject{
private:
public:
    chest(){}

    void interact() override{
        std::cout << "chest has been interacted with: "  << objectID << std::endl;
    }
};

#endif