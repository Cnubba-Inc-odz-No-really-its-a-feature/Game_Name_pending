#ifndef _LANE_HPP
#define _LANE_HPP

#include "laneStructs.hpp"

///\brief
/// The class that manages the units on the lanes
///\details
/// two lanes are currently implemented, the sky and the ground. ally and enemy movements are independendly updated
/// aswell as a fight phase. 
class lane{
private:
    E_lane laneID;
    int& playerHP;
    int& enemyHP;

    std::array<std::shared_ptr<unit>, LANE_SIZE> allyArray;
    std::array<std::shared_ptr<unit>, LANE_SIZE> enemyArray;
    std::shared_ptr<nullUnit> nullUnitPointer;
public:

    ///\brief
    ///Constructor, gets is lane type and the hp's of both players
    lane(E_lane laneID, int& playerHP, int& enemyHP);

    ///\brief
    /// Returns whether a place on the board is empty
    bool isIndexEmpty(const int index);

    ///\brief
    /// Places a unit on the board
    void placeUnit(std::shared_ptr<unit> unitPointer);

    ///\brief
    /// Resets the lane in preperation for a new fight
    void reset();

    // updates and combat
    ///\brief
    /// Updates the ally array and line, does the movement
    void updateAllyLane();

    ///\brief
    /// Updates the enemy array and line, does the movement
    void updateEnemyLane();

    ///\brief
    /// Updates an indivdual unit
    void updateUnit(const int index, std::shared_ptr<unit> unit);

    ///\brief
    /// Resolves the combat phase of the fight
    void fightPhase();

    ///\brief
    /// Calculates the outcome of a fight
    combatResult fight(std::shared_ptr<unit> initiator, std::shared_ptr<unit> assaulted, const int index);

    // draw functions
    ///\brief
    /// gets the location of the first place in the lane     
    sf::Vector2f getLaneStartPosition(E_lane laneID, sf::RenderWindow& window);

    ///\brief
    /// Gets the next lane location
    float getIterationDistanceX(sf::RenderWindow& window);

    ///\brief
    /// Draws the current state of the lane with its unit in it.
    void draw(sf::RenderWindow& window);

    ///\brief
    /// debug function that prints the current state in the terminal
    void print_array();

};

#endif