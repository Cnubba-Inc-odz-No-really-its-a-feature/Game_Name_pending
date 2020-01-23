#include "objectStorage.hpp"

std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> & objectStorage::getActive(){
        return allVectors[keyActive];
    }

void objectStorage::setActive(std::string newKey){
    swappedActive = true;
    tmpActive = newKey;
}

objectStorage::objectStorage():
    menu(new std::vector<std::shared_ptr<gameObject>>), 
    game(new std::vector<std::shared_ptr<gameObject>>), 
    title(new std::vector<std::shared_ptr<gameObject>>)
{
    allVectors.insert({"Menu", menu});
    allVectors.insert({"Game", game});
    allVectors.insert({"Title", title});
}
auto ref = std::make_shared<std::shared_ptr<gameObject>[LANE_SIZE]>();

boardLaneArraysContainer objectStorage::getLaneArrays(){
    return boardLaneArraysContainer(
                                    laneArrayContainer(std::make_shared<std::array<std::shared_ptr<gameObject>, LANE_SIZE>>(allyArrayAir),
                                                std::make_shared<std::array<std::shared_ptr<gameObject>, LANE_SIZE>>(enemyArrayAir)),
                                    laneArrayContainer(std::make_shared<std::array<std::shared_ptr<gameObject>, LANE_SIZE>>(allyArrayGround),
                                                std::make_shared<std::array<std::shared_ptr<gameObject>, LANE_SIZE>>(enemyArrayGround)), 
                                    laneArrayContainer(std::make_shared<std::array<std::shared_ptr<gameObject>, LANE_SIZE>>(allyArrayTraps),
                                                std::make_shared<std::array<std::shared_ptr<gameObject>, LANE_SIZE>>(enemyArrayTraps))
                                    );
}