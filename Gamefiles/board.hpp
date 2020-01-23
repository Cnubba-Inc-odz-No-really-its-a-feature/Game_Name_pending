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
    board(boardLaneArraysContainer& boardContainer);

    board(const sf::Texture& boardTexture, boardLaneArraysContainer& boardContainer);

    void update();

    void updateUnitsOnAllLanes(const int E_lane);

    void updateEffectsOnAllLanes(const int E_lane);

    void updateLane(const int E_lane);

    void updateUnitsOnLane(const int E_lane);

    void updateEffectsOnLane(const int E_lane);

    void placeUnit(const int E_lane, const int index, std::shared_ptr<gameObject> unitPointer);
    
    void placeTrapcard(const int index, std::shared_ptr<gameObject> trapcardPointer);

    void placeEffect(const int E_lane, const int index, std::shared_ptr<gameObject> effectPointer);

    void castSpell(const int E_lane, const int index, std::shared_ptr<gameObject> spell);

    void removeUnit(const int E_lane, const int index);

    void removeEffect(const int E_lane, const int index, const int effectIndex);

    void removeByID(const std::string& id);

    std::shared_ptr<gameObject> getUnitPointer(const int E_lane, const int laneIndex);

    std::shared_ptr<gameObject> getUnitPointerByID(const std::string& id);

    bool isPositionEmpty(const int E_lane, const int index);

    bool isTrapCardOnPosition(const int index);

    void draw(sf::RenderWindow& window);
};

#endif