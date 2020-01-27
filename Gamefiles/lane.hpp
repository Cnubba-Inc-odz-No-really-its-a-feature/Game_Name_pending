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
    // constructors
    lane(E_lane laneID, int_fast8_t & playerHP, int_fast8_t & enemyHP);

    // checks
    bool isIndexEmpty(const int index);

    // placements
    void placeUnit(std::shared_ptr<unit> unitPointer);

    // updates for fights
    void updateLane();
    void filterOutInValidResults(std::vector<unitUpdateResult>& rawResults);
    unitUpdateResult updateUnit(const int index, std::shared_ptr<unit> unit);
    unitUpdateResult fight(std::shared_ptr<unit> initiator, std::shared_ptr<unit> assaulted, const int index);
    
    // updates misc
    void updateAllUnits();

    // removes
    void removeAtIndex(const int index);
    void removeByID(const std::string& id);

    // get pointers
    std::shared_ptr<unit> getUnitPointerAtIndex(const int index);
    std::shared_ptr<unit> getUnitPointerByID(const std::string& id);

    // draw
    void draw(sf::RenderWindow& window);

};

#endif