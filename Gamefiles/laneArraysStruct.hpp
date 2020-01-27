#ifndef _LANE_ARRAYS_STRUCT_HPP
#define _LANE_ARRAYS_STRUCT_HPP

#include "memory"
#include "card.hpp"
#include "macrodefinitions.hpp"

struct laneArraysStruct{
    std::array<std::shared_ptr<unit>, LANE_SIZE>  allyArrayAir;
    std::array<std::shared_ptr<unit>, LANE_SIZE>  enemyArrayAir;
    std::array<std::shared_ptr<unit>, LANE_SIZE>  allyArrayGround;
    std::array<std::shared_ptr<unit>, LANE_SIZE>  enemyArrayGround;
    std::array<std::shared_ptr<unit>, LANE_SIZE>  allyArrayTraps;
    std::array<std::shared_ptr<unit>, LANE_SIZE>  enemyArrayTraps;

    laneArraysStruct(){
        std::cout<<"entered laneArray constructor" << std::endl;
        for(auto& unit : allyArrayAir){
            unit = nullptr;
        }
        for(auto& unit : enemyArrayAir){
            unit = nullptr;
        }
        for(auto& unit : allyArrayGround){
            unit = nullptr;
        }
        for(auto& unit : enemyArrayGround){
            unit = nullptr;
        }
        for(auto& unit : allyArrayTraps){
            unit = nullptr;
        }
        for(auto& unit : enemyArrayTraps){
            unit = nullptr;
        }

        std::cout << "laneArrayStruct created" << std::endl;
    }
};

#endif