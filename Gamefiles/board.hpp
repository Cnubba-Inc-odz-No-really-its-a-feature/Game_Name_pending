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
    // constructors
    board(boardLaneArraysContainer& boardContainer);
    board(const sf::Texture& boardTexture, boardLaneArraysContainer& boardContainer);

    // update functions
    void update();
    void updateUnitsOnAllLanes(const int E_lane);
    void updateEffectsOnAllLanes(const int E_lane);
    void updateLane(const int E_lane);
    void updateUnitsOnLane(const int E_lane);
    void updateEffectsOnLane(const int E_lane);

    // placements
    void placeUnit(const int E_lane, const int index, std::shared_ptr<gameObject> unitPointer);
    void placeTrapcard(const int index, std::shared_ptr<gameObject> trapcardPointer);
    void placeEffect(const int E_lane, const int index, std::shared_ptr<gameObject> effectPointer);

    //  spells
    void castSpell(const int E_lane, const int index, std::shared_ptr<gameObject> spell);

    // removes
    void removeUnit(const int E_lane, const int index);
    void removeEffect(const int E_lane, const int index, const int effectIndex);
    void removeByID(const std::string& id);

    // get pointers
    std::shared_ptr<gameObject> getUnitPointer(const int E_lane, const int laneIndex);
    std::shared_ptr<gameObject> getUnitPointerByID(const std::string& id);

    // checks
    bool isPositionEmpty(const int E_lane, const int index);
    bool isTrapCardOnPosition(const int index);
    
    // draw
    void draw(sf::RenderWindow& window);
};

#endif