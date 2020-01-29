#ifndef _LANE_STRUCTS_HPP
#define _LANE_STRUCTS_HPP

#include "memory"
#include "gameObject.hpp"
#include "macrodefinitions.hpp"
#include "nullUnit.hpp"
#include "E_lane.hpp"

struct unitUpdateResult{
    int selfPosition;
    int opponentPosition;

    bool isAlly;
    bool openentKilled;
    bool selfKilled;
    bool valid;

    unitUpdateResult(bool valid, int selfPosition = 1, int opponentPosition = 1, bool oponentKilled = 1, bool selfKilled = 1, bool isAlly = 1):
        valid{valid},
        selfPosition{selfPosition},
        opponentPosition{opponentPosition},
        openentKilled{oponentKilled},
        selfKilled{selfKilled},
        isAlly{isAlly}
    {}
};


#endif