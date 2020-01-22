#ifndef _OBJECTSTORAGE_HPP_
#define _OBJECTSTORAGE_HPP_

#include "vector"
#include "memory"
#include "queue"
#include "gameObject.hpp"
#include "string"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "character.hpp"
#include "macrodefinitions.hpp"
#include "laneArrayContainer.hpp"

class objectStorage {
public:
    bool swappedActive = false;
    std::string tmpActive;
    std::string keyActive = "Title";
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> menu;
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> game;
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> title;
    std::map<std::string, std::shared_ptr<std::vector<std::shared_ptr<gameObject>>>> allVectors;

    std::array<std::shared_ptr<gameObject>, LANE_SIZE>  allyArrayAir;
    std::array<std::shared_ptr<gameObject>, LANE_SIZE>  enemyArrayAir;
    std::array<std::shared_ptr<gameObject>, LANE_SIZE>  allyArrayGround;
    std::array<std::shared_ptr<gameObject>, LANE_SIZE>  enemyArrayGround;
    std::array<std::shared_ptr<gameObject>, LANE_SIZE>  allyArrayTraps;
    std::array<std::shared_ptr<gameObject>, LANE_SIZE>  enemyArrayTraps;

    std::vector<std::shared_ptr<gameObject>> effectsLane1[LANE_SIZE];
    std::vector<std::shared_ptr<gameObject>> effectsLane2[LANE_SIZE];
    std::vector<std::shared_ptr<gameObject>> effectsLane3[LANE_SIZE];

    std::vector<gameObject> hand;
    std::vector<gameObject> drawpile;
    std::vector<gameObject> discardpile;
    std::vector<gameObject> completedeck;

    objectStorage();
    std::shared_ptr<gameObject> character1;
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> & getActive();


    void setActive(std::string newKey);
    boardLaneArraysContainer getLaneArrays();
};

#endif // _OBJECTSTORAGE_HPP_
