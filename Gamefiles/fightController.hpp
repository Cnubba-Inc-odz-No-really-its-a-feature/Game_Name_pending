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
    board gameBoard;


    int_fast8_t playerHP = 15;
    int_fast8_t enemyHP = 15;
    std::shared_ptr<int_fast8_t> playerHPPointer = std::make_shared<int_fast8_t>(playerHP);
    std::shared_ptr<int_fast8_t> enemyHPPointer = std::make_shared<int_fast8_t>(enemyHP);
    E_fightState fightState;

    E_fightState updateFightState(){
        if(playerHP >= 0 && enemyHP <= 0){
            fightState = E_fightState::win;
        }
        else if(playerHP <= 0 && enemyHP >= 0){
            fightState = E_fightState::loss;
        }
        else if(playerHP <= 0 && enemyHP <= 0){
            fightState = E_fightState::draw;
        }
        else{
            fightState = E_fightState::inCombat;
        }
        return fightState;
    }

public:
    fightController(const boardLaneArraysContainer& boardContainer):
        gameBoard{boardContainer, playerHPPointer, enemyHPPointer}
    {
        std::cout << "fightController made" << std::endl;
    }

    void initFight(){}

    void nextTurn(){
        gameBoard.update();
        updateFightState();

        // add menu stuff
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