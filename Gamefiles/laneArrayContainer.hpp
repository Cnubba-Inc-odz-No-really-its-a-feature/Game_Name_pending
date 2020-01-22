#ifndef _LANE_ARRAY_CONTAINER
#define _LANE_ARRAY_CONTAINER

#include "memory"
#include "gameObject.hpp"
#include "macrodefinitions.hpp"

struct boardLaneArraysContainer{
    laneArrayContainer airLane;
    laneArrayContainer groundLane;
    laneArrayContainer trapLane;
};

struct laneArrayContainer{
    std::shared_ptr<std::shared_ptr<gameObject>[LANE_SIZE]> allyArray;
    std::shared_ptr<std::shared_ptr<gameObject>[LANE_SIZE]> enemyArray;
};

#endif