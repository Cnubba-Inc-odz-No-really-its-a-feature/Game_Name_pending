#ifndef _NULL_UNIT_HPP
#define _NULL_UNIT_HPP

#include "card.hpp"

///\brief
/// class used for debugging and creating empty units
class nullUnit : public unit{
private:
public:
    ///\brief
    /// class used for debugging and creating empty units
    nullUnit():
        unit()
    {}
    ///\brief
    /// class used for debugging and creating empty units
    void draw(sf::RenderWindow& gameWindow) override{

    }
};

#endif