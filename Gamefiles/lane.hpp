#ifndef _LANE_HPP
#define _LANE_HPP

#include "laneStructs.hpp"

class lane{
private:
    E_lane laneID;
    std::shared_ptr<int_fast8_t> playerHP;
    std::shared_ptr<int_fast8_t> enemyHP;

    std::shared_ptr<std::array<std::shared_ptr<unit>, LANE_SIZE>> allyArray;
    std::shared_ptr<std::array<std::shared_ptr<unit>, LANE_SIZE>> enemyArray;
    std::array<std::vector<std::shared_ptr<gameObject>>, 7> laneEffects;
public:
    // constructors
    lane();
    lane(E_lane laneID, std::shared_ptr<int_fast8_t> playerHP,std::shared_ptr<int_fast8_t> enemyHP, laneArrayContainer& laneArrays);

    // checks
    bool isIndexEmpty(const int index);

    // placements
    void placeUnit(std::shared_ptr<unit> unitPointer);
    void placeUnit(const int index, std::shared_ptr<unit> unitPointer);
    void placeEffect(const int index, std::shared_ptr<gameObject> effectPointer);

    // updates for fights
    void updateLane();
    void filterOutInValidResults(std::vector<unitUpdateResult>& rawResults);
    unitUpdateResult updateUnit(const int index, std::shared_ptr<unit> unit);
    unitUpdateResult fight(std::shared_ptr<unit> initiator, std::shared_ptr<unit> assaulted, const int index);
    
    // updates misc
    void updateAllUnits();
    void updateEffects();

    // removes
    void removeAtIndex(const int index);
    void removeEffectAtIndex(const int positionIndex, const int effectIndex);
    void removeByID(const std::string& id);

    // get pointers
    std::shared_ptr<unit> getUnitPointerAtIndex(const int index);
    std::shared_ptr<unit> getUnitPointerByID(const std::string& id);

    // draw
    void draw(sf::RenderWindow& window);

};

#endif