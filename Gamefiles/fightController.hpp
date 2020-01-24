#ifndef _FIGHT_CONTROLLER_HPP
#define _FIGHT_CONTROLLER_HPP

#include "card.hpp"
#include "board.hpp"
#include "objectStorage.hpp"

enum class E_fightState{
    win,
    loss,
    draw,
    inCombat
};

class fightController{
private:
    std::shared_ptr<objectStorage> storage;
    board gameBoard;

    int playerHP = 15;
    int enemyHP = 15;
    E_fightState fightState;

    E_fightState updateFightState(){
        switch(playerHP, enemyHP){
            if(playerHP >=0 && enemyHP <=0){
                fightState = E_fightState::win;
            }
            else if(playerHP <=0 && enemyHP >= 0){
                fightState = E_fightState::loss;
            }
            else if(playerHP <=0 && enemyHP <= 0){
                fightState = E_fightState::draw;
            }
            else{
                fightState = E_fightState::inCombat;
            }
        }
        return fightState;
    }

public:
    fightController(objectStorage& storage, boardLaneArraysContainer boardContainer):
        storage{std::make_shared<objectStorage>(storage)},
        gameBoard{boardContainer, std::make_shared<int>(playerHP), std::make_shared<int>(enemyHP)}
    {}

    void initFight(){}

    void nextTurn(){
        gameBoard.update();
        updateFightState();

        if(fightState != E_fightState::inCombat){
            switch(fightState){
                case E_fightState::win:
                    break;
                case E_fightState::loss:
                    break;
                case E_fightState::draw:
                    break;
            }
        }
    }

    bool placeUnitOnBoard(std::shared_ptr<unit> unitPointer){
        return gameBoard.placeUnit(unitPointer);
    }

};

#endif