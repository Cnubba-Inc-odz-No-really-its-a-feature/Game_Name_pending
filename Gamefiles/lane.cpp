#include "lane.hpp"
    
    lane::lane(E_lane laneID, int_fast8_t &playerHP, int_fast8_t& enemyHP):
        laneID{laneID},
        playerHP{playerHP},
        enemyHP{enemyHP}
    {
        nullUnitPointer = std::make_shared<nullUnit>();
        allyArray = {nullUnitPointer, nullUnitPointer, nullUnitPointer, nullUnitPointer, nullUnitPointer, nullUnitPointer, nullUnitPointer};
        enemyArray = {nullUnitPointer, nullUnitPointer, nullUnitPointer, nullUnitPointer, nullUnitPointer, nullUnitPointer, nullUnitPointer};
        std::cout << "lane made" << std::endl;
    }

    bool lane::isIndexEmpty(const int index){
        return allyArray.at(index) == nullUnitPointer && enemyArray.at(index) == nullUnitPointer;
    }

    std::shared_ptr<unit> lane::getUnitPointerAtIndex(const int index){
        if(allyArray.at(index) == nullUnitPointer){
            return enemyArray.at(index);
        }
        else{
            return allyArray.at(index);
        }
    }

    void lane::placeUnit(std::shared_ptr<unit> unitPointer){
        if(unitPointer->isAlly()){
            allyArray.at(0) = unitPointer;
        }
    }

    void lane::updateLane(){
        std::vector<unitUpdateResult> updateResults = {};
        
        // update allies
        for(uint_fast8_t i = LANE_SIZE -1; i >= 0; i--){
            updateResults.push_back(updateUnit(i, allyArray.at(i)));
        }

        // filter result of fights and act on it
        filterOutInValidResults(updateResults);
        for(auto& result : updateResults){
            if(result.openentKilled){
                enemyArray.at(result.opponentPosition) = nullUnitPointer;
            }
            if(result.selfKilled){
                allyArray.at(result.selfPosition) = nullUnitPointer;
            }
        }

        // update enemies
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            updateResults.push_back(updateUnit(i, enemyArray.at(i)));
        }

        // filter result of fights and act on it
        filterOutInValidResults(updateResults);
        for(auto& result : updateResults){
            if(result.openentKilled){
                allyArray.at(result.opponentPosition) = nullUnitPointer;
            }
            if(result.selfKilled){
                enemyArray.at(result.selfPosition) = nullUnitPointer;
            }
        }

        // set drawingPosition for the units
        sf::Vector2f laneStartPosition = lanePositionMap[laneID];

        sf::Vector2f drawPosition = laneStartPosition;
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            allyArray.at(i)->jumpLocationTo(drawPosition);
            drawPosition.x += 350;
        }
        
        drawPosition = laneStartPosition;
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            enemyArray.at(i)->jumpLocationTo(drawPosition);
            drawPosition.x += 350;
        }
    }

    void lane::filterOutInValidResults(std::vector<unitUpdateResult>& rawResults){
        std::vector<unitUpdateResult> cleanVector;
        for(const auto result : rawResults){
            if(result.valid){
                cleanVector.push_back(result);
            }
        }

        rawResults = cleanVector;
    }

    unitUpdateResult lane::updateUnit(const int index, std::shared_ptr<unit> unit){
        if(unit->isAlly()){
            if(index + 1 < LANE_SIZE && isIndexEmpty(index + 1)){
                allyArray.at(index + 1) = unit;
                allyArray.at(index) = nullUnitPointer;
            }
            else if(index == LANE_SIZE - 1){
                enemyHP -= unit->getDamage();
            }
            else if(index + 1 < LANE_SIZE){
                unitUpdateResult result = fight(unit, enemyArray.at(index + 1), index);

                if(result.openentKilled && !result.selfKilled){
                    allyArray.at(index + 1) = unit;
                    allyArray.at(index) = nullUnitPointer;
                }

                return result;
            }

                return unitUpdateResult(false);
        }
        else{
            if(index - 1 > 0 && isIndexEmpty(index - 1)){
                enemyArray.at(index - 1) = unit;
                enemyArray.at(index) = nullUnitPointer;
            }
            else if(index == 0){
                playerHP -= unit->getDamage();
            }
            else if(index > 0){
                unitUpdateResult result = fight(unit, allyArray.at(index - 1), index);

                if(result.openentKilled && !result.selfKilled){
                    enemyArray.at(index - 1) = unit;
                    enemyArray.at(index) = nullUnitPointer;
                }

                return result;
            }
            
            return unitUpdateResult(false);
        }
    }

    unitUpdateResult lane::fight(std::shared_ptr<unit> initiator, std::shared_ptr<unit> assaulted, const int index){
        assaulted->takeDamage(initiator->getDamage());
        initiator->takeDamage(assaulted->getDamage());

        int selfPosition = index;
        int opponentPosition;

        if(initiator->isAlly()){
            opponentPosition = index + 1;
        }
        else{
            opponentPosition = index - 1;
        }

        bool selfKilled = initiator->checkIsDead();
        bool opponentKilled = assaulted->checkIsDead();

        return unitUpdateResult(1, selfPosition, opponentPosition ,opponentKilled, selfKilled);
    }
    
    void lane::updateAllUnits(){
        std::vector<unitUpdateResult> updateResults = {};
        
        // update allies
        for(uint_fast8_t i = LANE_SIZE -1; i >= 0; i--){
            updateResults.push_back(updateUnit(i, allyArray.at(i)));
        }

        // filter result of fights and act on it
        filterOutInValidResults(updateResults);
        for(auto& result : updateResults){
            if(result.openentKilled){
                enemyArray.at(result.opponentPosition) = nullUnitPointer;
            }
            if(result.selfKilled){
                allyArray.at(result.selfPosition) = nullUnitPointer;
            }
        }

        // update enemies
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            updateResults.push_back(updateUnit(i, enemyArray.at(i)));
        }

        // filter result of fights and act on it
        filterOutInValidResults(updateResults);
        for(auto& result : updateResults){
            if(result.openentKilled){
                allyArray.at(result.opponentPosition) = nullUnitPointer;
            }
            if(result.selfKilled){
                enemyArray.at(result.selfPosition) = nullUnitPointer;
            }
        }

        // set positions of the unit sprites
        sf::Vector2f laneStartPosition = lanePositionMap[laneID];

        sf::Vector2f drawPosition = laneStartPosition;
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            allyArray.at(i)->jumpLocationTo(drawPosition);
            drawPosition.x += 350;
        }
        
        drawPosition = laneStartPosition;
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            enemyArray.at(i)->jumpLocationTo(drawPosition);
            drawPosition.x += 350;
        }
    }

    void lane::removeAtIndex(const int index){
        allyArray.at(index) = nullUnitPointer;
        enemyArray.at(index) = nullUnitPointer;
    }

    void lane::removeByID(const std::string& id){
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            if(allyArray.at(i)->getObjectID() == id){
                allyArray.at(i) = nullUnitPointer;
            }

            if(enemyArray.at(i)->getObjectID() == id){
                enemyArray.at(i) = nullUnitPointer;
            }
        }
    }

    std::shared_ptr<unit> lane::getUnitPointerByID(const std::string& id){
        for(auto& unit : allyArray){
            if(unit->getObjectID() == id){
                return unit;
            }
        }
        for(auto& unit : enemyArray){
            if(unit->getObjectID() == id){
                return unit;
            }
        }
        return nullUnitPointer;
    }

    void lane::draw(sf::RenderWindow& window){
        sf::Vector2f laneStartPosition = lanePositionMap[laneID];

        sf::Vector2f drawPosition = laneStartPosition;
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            allyArray.at(i)->jumpLocationTo(drawPosition);
            allyArray.at(i)->draw(window);

            drawPosition.x += 350;
        }
        
        drawPosition = laneStartPosition;
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            enemyArray.at(i)->jumpLocationTo(drawPosition);
            enemyArray.at(i)->draw(window);

            drawPosition.x += 350;
        }
    }
