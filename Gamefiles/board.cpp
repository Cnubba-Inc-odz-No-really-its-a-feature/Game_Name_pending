#include "board.hpp"

board::board(boardLaneArraysContainer& boardContainer, std::shared_ptr<int> playerHP, std::shared_ptr<int> enemyHP):
        priorityLane{E_lane::skyLane},
        playerHP{playerHP},
        enemyHP{enemyHP}
    {
        lanes[E_lane::skyLane] = lane(E_lane::skyLane, std::make_shared<int>(playerHP), std::make_shared<int>(enemyHP), boardContainer.skyLane);
        lanes[E_lane::groundLane] = lane(E_lane::groundLane, std::make_shared<int>(playerHP), std::make_shared<int>(enemyHP), boardContainer.groundLane);
        lanes[E_lane::trapLane] = lane(E_lane::trapLane, std::make_shared<int>(playerHP), std::make_shared<int>(enemyHP), boardContainer.trapLane);
    }

    void board::update(){
        lanes[priorityLane].updateLane();
        
        for(uint_fast8_t i = 0; i < 3; i++){
            if(i != priorityLane){
                lanes[i].updateLane();
            }
        }
    }

    void board::updateUnitsOnAllLanes(const int E_lane){
        for(lane& currentLane : lanes){
            currentLane.updateAllUnits();
        }
    }

    void board::updateEffectsOnAllLanes(const int E_lane){
        for(lane& currentLane : lanes){
            currentLane.updateLane();
        }
    }

    void board::updateLane(const int E_lane){
        lanes[E_lane].updateLane();
    }

    void board::updateUnitsOnLane(const int E_lane){
        lanes[E_lane].updateAllUnits();
    }

    void board::updateEffectsOnLane(const int E_lane){
        lanes[E_lane].updateEffects();
    }

    bool placeUnit(std::shared_ptr<unit> unitPointer){
        if(lanes[unit->laneType].isIndexEmpty(0)){
            lanes[unit->laneType].placeUnit(unitPointer);
            return true;
        }
        return false;
    }

    void board::placeUnit(const int E_lane, const int index, std::shared_ptr<gameObject> unitPointer){
        if(index >=0 && index < LANE_SIZE){
            lanes[E_lane].placeUnit(index, unitPointer);
        }
        else{
            std::cout << "index out of range" << std::endl;
        }
    }
    
    void board::placeTrapcard(const int index, std::shared_ptr<gameObject> trapcardPointer){
        if(index >=0 && index < LANE_SIZE){
            lanes[E_lane::trapLane].placeUnit(index, trapcardPointer);
        }
        else{
            std::cout << "index out of range" << std::endl;
        }
    }

    void board::placeEffect(const int E_lane, const int index, std::shared_ptr<gameObject> effectPointer){
        if(index >=0 && index < LANE_SIZE){
            lanes[E_lane].placeEffect(index, effectPointer);
        }
        else{
            std::cout << "index out of range" << std::endl;
        }
    }

    void board::castSpell(const int E_lane, const int index, std::shared_ptr<gameObject> spell){
        spell.activate(&lanes, E_lane, index);
    }

    void board::removeUnit(const int E_lane, const int index){
        lanes[E_lane].removeAtIndex(index);
    }

    void board::removeEffect(const int E_lane, const int index, const int effectIndex){
        lanes[E_lane].removeEffectAtIndex(index, effectIndex);
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

    bool board::isTrapCardOnPosition(const int index){
        return lanes[E_lane::trapLane].isIndexEmpty(index);
    }

    void board::draw(sf::RenderWindow& window){
        for(auto& currentLane : lanes){
            currentLane.draw(window);
        }
    }