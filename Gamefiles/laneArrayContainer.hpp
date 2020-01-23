#ifndef _LANE_ARRAY_CONTAINER
#define _LANE_ARRAY_CONTAINER

#include "memory"
// #include "unit.hpp"
#include "card.hpp"
#include "macrodefinitions.hpp"

struct laneArrayContainer{
    std::shared_ptr<std::array<std::shared_ptr<unit>, LANE_SIZE>>  allyArray;
    std::shared_ptr<std::array<std::shared_ptr<unit>, LANE_SIZE>>  enemyArray;

    laneArrayContainer(std::shared_ptr<std::array<std::shared_ptr<unit>, LANE_SIZE>>  allyArray, std::shared_ptr<std::array<std::shared_ptr<unit>, LANE_SIZE>> enemyArray):
        allyArray{allyArray},
        enemyArray{enemyArray}
    {}
};

struct boardLaneArraysContainer{
    laneArrayContainer skyLane;
    laneArrayContainer groundLane;
    laneArrayContainer trapLane;

    boardLaneArraysContainer(laneArrayContainer skyLane, laneArrayContainer groundLane, laneArrayContainer trapLane):
        skyLane{skyLane},
        groundLane{groundLane},
        trapLane{trapLane}
    {}
};

#endif