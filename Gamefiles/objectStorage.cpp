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

boardLaneArraysContainer objectStorage::getLaneArrays(){
    return boardLaneArraysContainer(
                                    laneArrayContainer(std::shared_ptr<std::shared_ptr<gameObject>[LANE_SIZE]>(allyArrayAir),
                                                std::shared_ptr<std::shared_ptr<gameObject>[LANE_SIZE]>(EnemyArrayAir)),
                                    laneArrayContainer(std::shared_ptr<std::shared_ptr<gameObject>[LANE_SIZE]>(allyArrayGround),
                                                std::shared_ptr<std::shared_ptr<gameObject>[LANE_SIZE]>(allyArrayGround)), 
                                    laneArrayContainer(std::shared_ptr<std::shared_ptr<gameObject>[LANE_SIZE]>(allyArrayTraps),
                                                std::shared_ptr<std::shared_ptr<gameObject>[LANE_SIZE]>(EnemyArrayTraps))
                                    );
}