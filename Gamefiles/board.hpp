#ifndef _BOARD_HPP
#define _BOARD_HPP

#include "lane.hpp"

class board {
private:
    lane lanes[3];
    E_lane priorityLane;

    int_fast8_t & playerHP;
    int_fast8_t & enemyHP;
public:
    board(int_fast8_t &playerHP, int_fast8_t & enemyHP);

    void update();
    bool placeUnit(std::shared_ptr<unit> unitPointer);
    bool isPositionEmpty(const int E_lane, const int index);
    void draw(sf::RenderWindow& window);
};

#endif