#ifndef _BOARD_HPP
#define _BOARD_HPP

#include "lane.hpp"

class board {
private:
    /// \brief
    /// All lanes, currently is the third lane, the trap lane, not implemented.
    lane lanes[3];
    /// \brief
    /// Not used. Nessesry for future buff systems
    E_lane priorityLane;

    int_fast8_t & playerHP;
    int_fast8_t & enemyHP;
public:
    board(int_fast8_t &playerHP, int_fast8_t & enemyHP);

    bool getSkyOpen();
    bool getGroundOpen();

    int_fast8_t GetHP(std::string who);

    void update();
    bool placeUnit(std::shared_ptr<unit> unitPointer);
    bool isPositionEmpty(const int E_lane, const int index);
    void draw(sf::RenderWindow& window);

    void reset();
};

#endif