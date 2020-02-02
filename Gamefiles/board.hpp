#ifndef _BOARD_HPP
#define _BOARD_HPP

#include "lane.hpp"
#include "UI.hpp"

class board {
private:
    /// \brief
    /// All lanes, currently is the third lane, the trap lane, not implemented.
    lane lanes[3];

    /// \brief
    /// Not used. Nessesry for future buff systems.
    E_lane priorityLane;

    /// \brief
    /// Tracks players hp so the lanes can update the current hp
    int & playerHP;

    /// \brief
    /// Tracks enemy hp so the lanes can update the current hp
    int & enemyHP;

    /// \brief
    /// Tracks player mana, increments every turn
    int & playerMana;

    /// \brief
    /// Tracks enemy mana, in final product not used
    int & enemyMana;

    /// \brief
    /// UI object, displays all the current stats during the fight
    UI combatUI;


public:

    /// \brief
    /// The board constructor.
    /// \details
    /// The constructor needs playerHP and enemyHP, both by reference. 
    board(int & playerHP, int & enemyHP, int & playerMana, int & enemyMana);

    /// \brief
    /// Returns true if the first place in the sky lane is open to place a card on.
    bool getSkyOpen();

    /// \brief
    /// Returns true if the first place in the ground lane is open to place a card on.
    bool getGroundOpen();

    /// \brief
    /// Updates the board to resolve fights and move cards forward one tick. Called once every turn.
    void update(bool player);

    /// \brief
    /// Updates the enemy array in all lanes
    void updateEnemy();
    
    /// \brief
    /// Updates the ally array in all lanes
    void updateAlly();
    
    /// \brief
    /// Resolves fight phase of the board
    void fightPhase();

    ///\brief
    /// Last call in the cyle, updates the ui to the new state
    void updateStatsUI();

    /// \brief
    /// places a unit on the field and returns whether operation was succesfull.
    bool placeUnit(std::shared_ptr<unit> unitPointer);

    /// \brief
    /// Returns whether a specific place on the board is empty.
    bool isPositionEmpty(const int E_lane, const int index);

    /// \brief
    /// Gets called every frame to draw all the board.
    void draw(sf::RenderWindow& window);

    /// \brief
    /// gets called at the start of the cardgame, to ensure a clean en ready board.
    void reset();
};

#endif