#ifndef _LANE_HPP
#define _LANE_HPP

// #include "laneStructs.hpp"
#include "memory"
#include "gameObject.hpp"
#include "macrodefinitions.hpp"
#include "laneArrayContainer.hpp"
#include "enums.hpp"

std::map<E_lane, sf::Vector2f> lanePositionMap1{
    {E_lane::skyLane, sf::Vector2f(500, 200)},
    {E_lane::groundLane, sf::Vector2f(500, 600)},
    {E_lane::trapLane, sf::Vector2f(500, 900)}
};

struct unitUpdateResult{
    int selfPosition;
    int opponentPosition;

    bool openentKilled;
    bool selfKilled;
    bool valid;

    unitUpdateResult(bool valid, int selfPosition = 1, int opponentPosition = 1, bool oponentKilled = 1, bool selfKilled = 1):
        valid{valid},
        selfPosition{selfPosition},
        opponentPosition{opponentPosition},
        openentKilled{oponentKilled},
        selfKilled{selfKilled}
    {}
};

class lane{
private:
    E_lane laneID;
    std::shared_ptr<int> playerHP;
    std::shared_ptr<int> enemyHP;

    std::shared_ptr<std::array<std::shared_ptr<unit>, LANE_SIZE>> allyArray;
    std::shared_ptr<std::array<std::shared_ptr<unit>, LANE_SIZE>> enemyArray;
    std::array<std::vector<std::shared_ptr<gameObject>>, 7> laneEffects;
public:
    // constructors
    lane();
    lane(E_lane laneID, std::shared_ptr<int> playerHP,std::shared_ptr<int> enemyHP, laneArrayContainer& laneArrays);

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