#ifndef _BOARD_HPP
#define _BOARD_HPP

#include "lane.hpp"

class board {
private:
    lane lanes[3];
    sf::Sprite boardSprite;
    E_lane priorityLane;

    int playerHP = 5;
    int enemyHP = 5;
public:
    board(boardLaneArraysContainer& boardContainer):
        priorityLane{E_lane::skyLane}
    {
        lanes[E_lane::skyLane] = lane(std::make_shared<int>(playerHP), std::make_shared<int>(enemyHP), boardContainer.skyLane);
        lanes[E_lane::groundLane] = lane(std::make_shared<int>(playerHP), std::make_shared<int>(enemyHP), boardContainer.groundLane);
        lanes[E_lane::trapLane] = lane(std::make_shared<int>(playerHP), std::make_shared<int>(enemyHP), boardContainer.trapLane);
    }

    board(const sf::Texture& boardTexture, boardLaneArraysContainer& boardContainer):
        boardSprite{boardTexture},
        priorityLane{E_lane::skyLane}
    {
        lanes[E_lane::skyLane] = lane(std::make_shared<int>(playerHP), std::make_shared<int>(enemyHP), boardContainer.skyLane);
        lanes[E_lane::groundLane] = lane(std::make_shared<int>(playerHP), std::make_shared<int>(enemyHP), boardContainer.groundLane);
        lanes[E_lane::trapLane] = lane(std::make_shared<int>(playerHP), std::make_shared<int>(enemyHP), boardContainer.trapLane);
    }

    void update(){
        lanes[priorityLane].updateLane(this);
        
        for(uint_fast8_t i = 0; i < 3; i++){
            if(i != priorityLane){
                lanes[i].updateLane(this);
            }
        }
    }

    void updateUnitsOnAllLanes(const int E_lane){
        for(lane& currentLane : lanes){
            currentLane.updateAllUnits(this);
        }
    }

    void updateEffectsOnAllLanes(const int E_lane){
        for(lane& currentLane : lanes){
            currentLane.updateLane(this);
        }
    }

    void updateLane(const int E_lane){
        lanes[E_lane].updateLane(this);
    }

    void updateUnitsOnLane(const int E_lane){
        lanes[E_lane].updateAllUnits(this);
    }

    void updateEffectsOnLane(const int E_lane){
        lanes[E_lane].updateEffects(this);
    }

    void placeUnit(const int E_lane, const int index, std::shared_ptr<gameObject> unitPointer){
        if(index >=0 && index < LANE_SIZE){
            lanes[E_lane].placeUnit(index, unitPointer);
        }
        else{
            std::cout << "index out of range" << std::endl;
        }
    }
    
    void placeTrapcard(const int index, std::shared_ptr<gameObject> trapcardPointer){
        if(index >=0 && index < LANE_SIZE){
            lanes[E_lane::trapLane].placeUnit(index, trapcardPointer);
        }
        else{
            std::cout << "index out of range" << std::endl;
        }
    }

    void placeEffect(const int E_lane, const int index, std::shared_ptr<gameObject> effectPointer){
        if(index >=0 && index < LANE_SIZE){
            lanes[E_lane].placeEffect(index, effectPointer);
        }
        else{
            std::cout << "index out of range" << std::endl;
        }
    }

    void castSpell(const int E_lane, const int index, std::shared_ptr<gameObject> spell){
        spell.activate(&lanes, E_lane, index);
    }

    void removeUnit(const int E_lane, const int index){
        lanes[E_lane].removeAtIndex(index);
    }

    void removeEffect(const int E_lane, const int index, const int effectIndex){
        lanes[E_lane].removeEffectAtIndex(index, effectIndex);
    }

    void removeByID(const std::string& id){
        for(lane& currentLane : lanes){
            currentLane.removeByID(id);
        }
    }

    std::shared_ptr<gameObject> getUnitPointer(const int E_lane, const int laneIndex){
        return lanes[E_lane].getUnitPointerAtIndex(laneIndex);
    }

    std::shared_ptr<gameObject> getUnitPointerByID(const std::string& id){
        std::shared_ptr<gameObject> unitPointer;

        for(auto& currentLane : lanes){
            unitPointer = currentLane.getUnitPointerByID(id);
            if(unitPointer != nullptr){
                return unitPointer;
            }
        }

        return nullptr;
    }

    bool isPositionEmpty(const int E_lane, const int index){
        return lanes[E_lane].isIndexEmpty(index);
    }

    bool isTrapCardOnPosition(const int index){
        return lanes[E_lane::trapLane].isIndexEmpty(index);
    }

    void draw(sf::RenderWindow& window){
        sf::Vector2f drawPosition = sf::Vector2f(window.getSize().x * 0.2, window.getSize().y * 0.2);
        window.draw(boardSprite);

        for(auto& currentLane : lanes){
            currentLane.draw(window, drawPosition);
            drawPosition.y += window.getSize().y *0.2;
            drawPosition.x = window.getSize().x * 0.2;
        }
    }
};

#endif