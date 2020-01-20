#ifndef _BOARD_HPP
#define _BOARD_HPP

#include "memory"
#include "gameObject.hpp"

#define LANE_SIZE 7




class lane{
private:
    std::shared_ptr<gameObject> laneArray[LANE_SIZE];
public:
    lane():
        laneArray{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
    {}

    bool isIndexEmpty(const int index){
        return laneArray[index] == nullptr;
    }

    std::shared_ptr<gameObject> getUnitPointerAtIndex(const int index){
        return laneArray[index];
    }

    void placeUnit(const int index, std::shared_ptr<gameObject> unitPointer){
        laneArray[index] = unitPointer;
    }

    void updateLane(){
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            laneArray[i]->update(i, laneArray);
        }
    }

    void removeAtIndex(const int index){
        laneArray[index] = nullptr;
    }
};


class board {
private:
    lane lanes[3];
public:
    board():
        lanes{lane(), lane(), lane()}
    {}

    void update(){
        for(lane& currentLane : lanes){
            currentLane.updateLane();
        }
    }

    void updateLane(const int E_lane){
        lanes[E_lane].updateLane();
    }

    void placeUnit(const int E_lane, const int laneIndex, std::shared_ptr<gameObject> unitPointer){
        lanes[E_lane].placeUnit(laneIndex, unitPointer);
    }

    //void castSpell(const int E_lane, const int index, std::shared_ptr<gameObject> spell){
    //   spell.activate(lanes, E_lane, index);
    //}

    void placeSpell(const int index, std::shared_ptr<gameObject> trapcardPointer){
        lanes[E_lane::trapLane].placeUnit(index, trapcardPointer);
    }

    std::shared_ptr<gameObject> getUnitPointer(const int E_lane, const int laneIndex){
        return lanes[E_lane].getUnitPointerAtIndex(laneIndex);
    }

};

#endif