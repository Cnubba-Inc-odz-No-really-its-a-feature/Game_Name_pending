#ifndef _LANE_HPP
#define _LANE_HPP

#include "laneStructs.hpp"

class lane{
private:
    std::shared_ptr<int> playerHP;
    std::shared_ptr<int> enemyHP;

    std::shared_ptr<std::array<std::shared_ptr<gameObject>, LANE_SIZE>> allyArray;
    std::shared_ptr<std::array<std::shared_ptr<gameObject>, LANE_SIZE>> enemyArray;
    std::vector<std::shared_ptr<gameObject>> laneEffects[LANE_SIZE];
public:
    // constructors
    lane();
    lane(std::shared_ptr<int> playerHP,std::shared_ptr<int> enemyHP, laneArrayContainer& laneArrays);

    // checks
    bool isIndexEmpty(const int index);

    // placements
    void placeUnit(const int index, std::shared_ptr<gameObject> unitPointer);
    void placeEffect(const int index, std::shared_ptr<gameObject> effectPointer);

    // updates for fights
    void updateLane(board* boardPointer);
    void filterOutInValidResults(std::vector<unitUpdateResult>& rawResults);
    unitUpdateResult fight(std::shared_ptr<gameObject> initiator, std::shared_ptr<gameObject> assaulted, const int index);
    
    // updates misc
    void updateAllUnits(board* boardPointer);
    void updateEffects(board* boardPointer);

    // removes
    void removeAtIndex(const int index);
    void removeEffectAtIndex(const int positionIndex, const int effectIndex);

    // get pointers
    std::shared_ptr<gameObject> getUnitPointerAtIndex(const int index);
    std::shared_ptr<gameObject> getUnitPointerByID(const std::string& id);

    // draw
    void draw(sf::RenderWindow& window, const sf::Vector2f& startPosition);

};

#endif