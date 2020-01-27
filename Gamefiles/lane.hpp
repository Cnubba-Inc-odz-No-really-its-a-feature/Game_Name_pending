#ifndef _LANE_HPP
#define _LANE_HPP

#include "laneStructs.hpp"

class lane{
private:
    E_lane laneID;
    int_fast8_t & playerHP;
    int_fast8_t & enemyHP;

    std::array<std::shared_ptr<unit>, LANE_SIZE> allyArray;
    std::array<std::shared_ptr<unit>, LANE_SIZE> enemyArray;
    std::shared_ptr<nullUnit> nullUnitPointer;
public:
    lane(E_lane laneID, int_fast8_t & playerHP, int_fast8_t & enemyHP);

    // for board
    bool isIndexEmpty(const int index);
    void placeUnit(std::shared_ptr<unit> unitPointer);
    void draw(sf::RenderWindow& window);
    void reset();

    // updates and combat
    void updateLane();
    unitUpdateResult updateUnits(const int index, std::shared_ptr<unit> unit);
    unitUpdateResult fight(std::shared_ptr<unit> initiator, std::shared_ptr<unit> assaulted, const int index);


};

#endif