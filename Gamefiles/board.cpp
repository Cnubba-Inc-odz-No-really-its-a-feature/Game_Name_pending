#include "board.hpp"
#include <iostream>
// board::board(){}

board::board(int_fast8_t & playerHP, int_fast8_t & enemyHP):
        lanes({
            lane(E_lane::skyLane, playerHP, enemyHP),
            lane(E_lane::groundLane, playerHP, enemyHP),
            lane(E_lane::trapLane, playerHP, enemyHP)
        }),
        priorityLane{E_lane::groundLane},
        playerHP{playerHP},
        enemyHP{enemyHP}
    {
        std::cout << "starting creation of board" << std::endl; 

        // lanes[E_lane::skyLane] = lane(E_lane::skyLane, playerHP, enemyHP, laneArrays->allyArrayAir, laneArrays->enemyArrayAir);
        // lanes[E_lane::groundLane] = lane(E_lane::groundLane, playerHP, enemyHP, laneArrays->allyArrayGround, laneArrays->enemyArrayGround);
        // lanes[E_lane::trapLane] = lane(E_lane::trapLane, playerHP, enemyHP, laneArrays->allyArrayTraps, laneArrays->enemyArrayTraps);

        std::cout << "board made" << std::endl; 
    }

    void board::update(){
        lanes[priorityLane].updateLane();
        
        for(uint_fast8_t i = 0; i < 3; i++){
            if(i != priorityLane){
                lanes[i].updateLane();
            }
        }
    }

    bool board::placeUnit(std::shared_ptr<unit> unitPointer){
        std::cout << "placing unit on board via board" << std::endl;
        if(lanes[unitPointer->getLaneType()].isIndexEmpty(0)){
            lanes[unitPointer->getLaneType()].placeUnit(unitPointer);
            std::cout << "board::placeUnit() success" << std::endl;
            return true;
        }
        return false;
    }

    void board::removeUnit(const int E_lane, const int index){
        lanes[E_lane].removeAtIndex(index);
    }

    void board::removeByID(const std::string& id){
        for(lane& currentLane : lanes){
            currentLane.removeByID(id);
        }
    }

    std::shared_ptr<gameObject> board::getUnitPointer(const int E_lane, const int laneIndex){
        return lanes[E_lane].getUnitPointerAtIndex(laneIndex);
    }

    std::shared_ptr<gameObject> board::getUnitPointerByID(const std::string& id){
        std::shared_ptr<gameObject> unitPointer;

        for(auto& currentLane : lanes){
            unitPointer = currentLane.getUnitPointerByID(id);
            if(unitPointer != nullptr){
                return unitPointer;
            }
        }

        return nullptr;
    }

    bool board::isPositionEmpty(const int E_lane, const int index){
        return lanes[E_lane].isIndexEmpty(index);
    }

    void board::draw(sf::RenderWindow& window){
        for(auto& currentLane : lanes){
            currentLane.draw(window);
        }
    }