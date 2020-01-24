#ifndef _LANE_STRUCTS_HPP
#define _LANE_STRUCTS_HPP

#include "memory"
#include "gameObject.hpp"
#include "macrodefinitions.hpp"
#include "laneArrayContainer.hpp"
#include "E_lane.hpp"

static std::map<E_lane, sf::Vector2f> lanePositionMap{
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


#endif