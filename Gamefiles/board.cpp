#include "board.hpp"
#include <iostream>
// board::board(){}

board::board(int & playerHP, int & enemyHP, int & playerMana, int & enemyMana ):
        lanes({
            lane(E_lane::skyLane, playerHP, enemyHP),
            lane(E_lane::groundLane, playerHP, enemyHP),
            lane(E_lane::trapLane, playerHP, enemyHP)
        }),
        priorityLane{E_lane::groundLane},
        playerHP(playerHP),
        enemyHP(enemyHP),
        playerMana{playerMana},
        enemyMana{enemyMana},
        combatUI(playerHP, enemyHP, playerMana)
    {}

    bool board::getSkyOpen(){
        return lanes[E_lane::skyLane].isIndexEmpty(0);
    }

    void board::fightPhase(){
        for(auto& lane : lanes){
            lane.fightPhase();
        }
    }

    bool board::getGroundOpen(){
        return lanes[E_lane::groundLane].isIndexEmpty(0);
    }

    void board::updateEnemy(){
        lanes[priorityLane].updateEnemyLane();
        
        for(uint_fast8_t i = 0; i < 3; i++){
            if(i != priorityLane){
                lanes[i].updateEnemyLane();
            }
        }
        combatUI.updateUI();

    }
    
    void board::updateAlly(){
        lanes[priorityLane].updateAllyLane();
        
        for(uint_fast8_t i = 0; i < 3; i++){
            if(i != priorityLane){
                lanes[i].updateAllyLane();
            }
        }

        combatUI.updateUI();

    }



    bool board::placeUnit(std::shared_ptr<unit> unitPointer){
        if(lanes[unitPointer->getLaneType()].isIndexEmpty(0)){
            lanes[unitPointer->getLaneType()].placeUnit(unitPointer);
            combatUI.updateUI();
            return true;
        }
        return false;
    }

    bool board::isPositionEmpty(const int E_lane, const int index){
        return lanes[E_lane].isIndexEmpty(index);
    }

    void board::draw(sf::RenderWindow& window){
        for(auto& currentLane : lanes){
            currentLane.draw(window);
        }
        combatUI.draw(window);
    }

    void board::reset(){
        for(auto& lane : lanes){
            std::cout << "reset lane \n";
            lane.reset();
        }
        combatUI.updateUI();
    }

