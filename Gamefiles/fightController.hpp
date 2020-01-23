#ifndef _FIGHT_CONTROLLER_HPP
#define _FIGHT_CONTROLLER_HPP

#include "card.hpp"
#include "board.hpp"
#include "objectStorage.hpp"

class fightController{
private:
    std::shared_ptr<objectStorage> storage;
    board gameBoard;

    int playerHP = 15;
    int enemyHP = 15;
public:
    fightController(objectStorage& storage, boardLaneArraysContainer boardContainer):
        storage{std::make_shared<objectStorage>(storage)},
        gameBoard{boardContainer, std::make_shared<int>(playerHP), std::make_shared<int>(enemyHP)}
    {}

    void initFight(){}

    void nextTurn(){
        gameBoard.update();
    }

    bool placeUnitOnBoard(std::shared_ptr<unit> unitPointer){
        return gameBoard.placeUnit(unitPointer);
    }

    void exitFight(){}

};

#endif