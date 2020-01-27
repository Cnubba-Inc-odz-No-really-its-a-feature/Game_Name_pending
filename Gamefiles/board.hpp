#ifndef _BOARD_HPP
#define _BOARD_HPP

#include "lane.hpp"

class board {
private:
    lane lanes[3];
    E_lane priorityLane;

    std::shared_ptr<int_fast8_t> playerHP;
    std::shared_ptr<int_fast8_t> enemyHP;
public:
    // constructors
    board();
    board(const boardLaneArraysContainer& boardContainer, std::shared_ptr<int_fast8_t> playerHP, std::shared_ptr<int_fast8_t> enemyHP);

    // update functions
    void update();

    // placements
    bool placeUnit(std::shared_ptr<unit> unitPointer);
    
    // removes
    void removeUnit(const int E_lane, const int index);
    void removeByID(const std::string& id);

    // get pointers
    std::shared_ptr<gameObject> getUnitPointer(const int E_lane, const int laneIndex);
    std::shared_ptr<gameObject> getUnitPointerByID(const std::string& id);

    // checks
    bool isPositionEmpty(const int E_lane, const int index);
    
    // draw
    void draw(sf::RenderWindow& window);
};

#endif