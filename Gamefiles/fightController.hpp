#ifndef _FIGHT_CONTROLLER_HPP
#define _FIGHT_CONTROLLER_HPP

#include "card.hpp"
#include "board.hpp"

class fightController{
private:
    deckClass deck;
    board gameBoard;
public:
    fightController(std::vector<std::shared_ptr<std::vector<int>>> deckVector, boardLaneArraysContainer boardContainer):
        deck{deckVector[0], deckVector[1], deckVector[2], deckVector[3]},
        gameBoard{boardContainer}
    {}
};

#endif