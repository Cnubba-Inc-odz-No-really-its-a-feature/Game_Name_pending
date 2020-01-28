#include "card.hpp"

std::ifstream& operator>>(std::ifstream& input, E_lane& unitLane){
        std::string laneString;
        input>>laneString;
        if(laneString == "groundLane"){
            unitLane = E_lane::groundLane;
            return input;
        }else if(laneString == "skyLane"){
            unitLane = E_lane::skyLane;
            return input;
        }else if(laneString == "traplane"){
            unitLane = E_lane::trapLane;
            return input;
        }else{
            throw invalid_UnitLane(std::string("invalid UnitLane at") + laneString);
        }
}
    