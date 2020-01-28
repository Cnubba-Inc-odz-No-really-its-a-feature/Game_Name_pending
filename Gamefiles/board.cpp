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
    {}

    bool board::getSkyOpen(){
        return lanes[E_lane::skyLane].isIndexEmpty(0);
    }

    bool board::getGroundOpen(){
        return lanes[E_lane::groundLane].isIndexEmpty(0);
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
        std::cout << "placing unit on board via board on lane: " << int(unitPointer->getLaneType()) << std::endl;
        if(lanes[unitPointer->getLaneType()].isIndexEmpty(0)){
            lanes[unitPointer->getLaneType()].placeUnit(unitPointer);
            std::cout << "board::placeUnit() success" << std::endl;
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
    }

    void board::reset(){
        for(auto& lane : lanes){
            lane.reset();
        }
    }