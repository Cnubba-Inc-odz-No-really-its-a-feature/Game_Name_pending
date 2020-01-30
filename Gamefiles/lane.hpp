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
    void reset();

    // updates and combat
    void updateAllyLane();
    void updateEnemyLane();
    void updateUnit(const int index, std::shared_ptr<unit> unit);
    unitUpdateResult fight(std::shared_ptr<unit> initiator, std::shared_ptr<unit> assaulted, const int index);

    // draw functions
    sf::Vector2f getLaneStartPosition(E_lane laneID, sf::RenderWindow& window);
    float getIterationDistanceX(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    void print_array();

};

#endif