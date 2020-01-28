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


    int_fast8_t playerHP;
    int_fast8_t enemyHP;
    //std::shared_ptr<int_fast8_t> playerHPPointer = std::make_shared<int_fast8_t>(playerHP);
    //std::shared_ptr<int_fast8_t> enemyHPPointer = std::make_shared<int_fast8_t>(enemyHP);
    E_fightState fightState;

public:
    fightController():
        playerHP{15},
        enemyHP{15},
        gameBoard{playerHP, enemyHP}
    {
        initFight();
    }

    void initFight(){
        gameBoard.reset();
        playerHP = 15;
        enemyHP = 15;
    }

    bool getSkyOpen(){
        return gameBoard.getSkyOpen();
    }

    bool getGroundOpen(){
        return gameBoard.getGroundOpen();
    }

    void nextTurn(){
        std::cout << "nextTurn()________________________________________________________________________" << std::endl;
        gameBoard.update();
        // add menu stuff
        if(playerHP <= 1 || enemyHP < 1){
            exit(0);
        }
    }

    bool placeUnitOnBoard(std::shared_ptr<unit> unitPointer){
        std::cout << "placing on board via fightController" << std::endl;
        bool success = gameBoard.placeUnit(unitPointer);
        std::cout << "unitPlacement: " << success << std::endl;
        return success;
    }

    void draw(sf::RenderWindow& window){
        gameBoard.draw(window);
    }

};

#endif