#ifndef _NULL_UNIT_HPP
#define _NULL_UNIT_HPP

#include "card.hpp"

class nullUnit : public unit{
private:
public:
    nullUnit():
        unit()
    {}


    void draw(sf::RenderWindow& gameWindow) override{

    }
};

#endif