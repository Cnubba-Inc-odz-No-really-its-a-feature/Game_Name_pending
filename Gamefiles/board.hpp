#ifndef _BOARD_HPP
#define _BOARD_HPP

#include "lane.hpp"

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
    int_fast8_t & playerHP;

    /// \brief
    /// Tracks enemy hp so the lanes can update the current hp
    int_fast8_t & enemyHP;

public:

    /// \brief
    /// The board constructor.
    /// \details
    /// The constructor needs playerHP and enemyHP, both by reference. 
    board(int_fast8_t & playerHP, int_fast8_t & enemyHP);

    /// \brief
    /// Returns true if the first place in the sky lane is open to place a card on.
    bool getSkyOpen();

    /// \brief
    /// Returns true if the first place in the ground lane is open to place a card on.
    bool getGroundOpen();

    /// \brief
    /// Updates the board to resolve fights and move cards forward one tick. Called once every turn.
    void update();

    /// \brief
    /// places a unit on the field and returns whether operation was succesfull.
    bool placeUnit(std::shared_ptr<unit> unitPointer);

    /// \brief
    /// Returns whether a specific place on the board is empty.
    bool isPositionEmpty(const int E_lane, const int index);

    /// \brief
    /// Gets called 
    void draw(sf::RenderWindow& window);

    void reset();
};

#endif