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

class objectStorage {
public:
    bool swappedActive = false;
    std::string tmpActive;
    std::string keyActive = "Title";
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> menu;
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> game;
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> title;
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> game_1;
    std::map<std::string, std::shared_ptr<std::vector<std::shared_ptr<gameObject>>>> allVectors;

    std::shared_ptr<gameObject> allyArrayLane1[LANE_SIZE];
    std::shared_ptr<gameObject> EnemyArrayLane1[LANE_SIZE];
    std::shared_ptr<gameObject> allyArrayLane2[LANE_SIZE];
    std::shared_ptr<gameObject> EnemyArrayLane2[LANE_SIZE];
    std::shared_ptr<gameObject> allyArrayLane3[LANE_SIZE];
    std::shared_ptr<gameObject> EnemyArrayLane3[LANE_SIZE];

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
};

#endif // _OBJECTSTORAGE_HPP_
