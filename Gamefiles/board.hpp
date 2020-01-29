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

    bool getSkyOpen();
    bool getGroundOpen();


    void update();
    bool placeUnit(std::shared_ptr<unit> unitPointer);
    bool isPositionEmpty(const int E_lane, const int index);
    void draw(sf::RenderWindow& window);

    void reset();
};

#endif