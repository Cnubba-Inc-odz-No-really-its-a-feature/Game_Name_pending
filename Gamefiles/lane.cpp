#include "lane.hpp"

    lane::lane(){}
    
    lane::lane(E_lane laneID, std::shared_ptr<int> playerHP,std::shared_ptr<int> enemyHP, laneArrayContainer& laneArrays):
        laneID{laneID},   
        allyArray{laneArrays.allyArray},
        enemyArray{laneArrays.enemyArray},
        playerHP{playerHP},
        enemyHP{enemyHP}
    {}

    bool lane::isIndexEmpty(const int index){
        return allyArray.get()->at(index) == nullptr && enemyArray.get()->at(index) == nullptr;
    }

    std::shared_ptr<gameObject> lane::getUnitPointerAtIndex(const int index){
        if(allyArray.get()->at(index) == nullptr){
            return enemyArray.get()->at(index);
        }
        else{
            return allyArray.get()->at(index);
        }
    }

    void lane::placeUnit(const int index, std::shared_ptr<gameObject> unitPointer){
        if(unitPointer->ally){
            allyArray.get()->at(index) = unitPointer;
        }
    }

    void lane::placeEffect(const int index, std::shared_ptr<gameObject> effectPointer){
        laneEffects[index].push_back(effectPointer);
    }

    void lane::updateLane(){
        std::vector<unitUpdateResult> updateResults = {};
        
        // update allies
        for(uint_fast8_t i = LANE_SIZE -1; i >= 0; i--){
            updateResults.push_back(updateUnit(i, allyArray.get()->at(i)));
        }

        // filter result of fights and act on it
        filterOutInValidResults(updateResults);
        for(auto& result : updateResults){
            if(result.openentKilled){
                enemyArray.get()->at(result.opponentPosition) = nullptr;
            }
            if(result.selfKilled){
                allyArray.get()->at(result.selfPosition) = nullptr;
            }
        }

        // update enemies
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            updateResults.push_back(updateUnit(i, enemyArray.get()->at(i)));
        }

        // filter result of fights and act on it
        filterOutInValidResults(updateResults);
        for(auto& result : updateResults){
            if(result.openentKilled){
                allyArray.get()->at(result.opponentPosition) = nullptr;
            }
            if(result.selfKilled){
                enemyArray.get()->at(result.selfPosition) = nullptr;
            }
        }

        // effects
        // for every position
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            // for every effect on that position
            for(uint_fast8_t j = 0; j < laneEffects[i].size(); j++){
                laneEffects[i][j]->update(i, j, this);
            }
        }

        // set drawingPosition for the units
        sf::Vector2f laneStartPosition = lanePositionMap[laneID];

        sf::Vector2f drawPosition = laneStartPosition;
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            allyArray->at(i)->jumpLocationTo(drawPosition);
            drawPosition.x += 350;
        }
        
        drawPosition = laneStartPosition;
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            enemyArray->at(i)->jumpLocationTo(drawPosition);
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

    unitUpdateResult lane::updateUnit(const int index, std::shared_ptr<gameObject> unit){
        if(unit->ally){
            if(index + 1 < LANE_SIZE && isIndexEmpty(index + 1)){
                allyArray.get()->at(index + 1) = unit;
                allyArray.get()->at(index) = nullptr;
            }
            else if(index == LANE_SIZE - 1){
                *enemyHP.get() -= unit.getDamage();
            }
            else if(index + 1 < LANE_SIZE){
                unitUpdateResult result = fight(unit, enemyArray.get()->at(index + 1), index);

                if(result.openentKilled && !result.selfKilled){
                    allyArray.get()->at(index + 1) = unit;
                    allyArray.get()->at(index) = nullptr;
                }

                return result;
            }

                return unitUpdateResult(false);
        }
        else{
            if(index - 1 > 0 && isIndexEmpty(index - 1)){
                enemyArray.get()->at(index - 1) = unit;
                enemyArray.get()->at(index) = nullptr;
            }
            else if(index == 0){
                *playerHP.get() -= unit.getDamage();
            }
            else if(index > 0){
                unitUpdateResult result = fight(unit, allyArray.get()->at(index - 1), index);

                if(result.openentKilled && !result.selfKilled){
                    enemyArray.get()->at(index - 1) = unit;
                    enemyArray.get()->at(index) = nullptr;
                }

                return result;
            }
            
            return unitUpdateResult(false);
        }
    }

    unitUpdateResult lane::fight(std::shared_ptr<gameObject> initiator, std::shared_ptr<gameObject> assaulted, const int index){
        assaulted.takeDamage(initiator.getDamage());
        initiator.takeDamage(assaulted.getDamage());

        int selfPosition = index;
        int opponentPosition;

        if(initiator->ally){
            opponentPosition = index + 1;
        }
        else{
            opponentPosition = index - 1;
        }

        bool selfKilled = initiator.checkIsDead();
        bool opponentKilled = assaulted.checkIsDead();

        return unitUpdateResult(1, selfPosition, opponentPosition ,opponentKilled, selfKilled);
    }
    
    void lane::updateAllUnits(){
        std::vector<unitUpdateResult> updateResults = {};
        
        // update allies
        for(uint_fast8_t i = LANE_SIZE -1; i >= 0; i--){
            updateResults.push_back(updateUnit(i, allyArray.get()->at(i)));
        }

        // filter result of fights and act on it
        filterOutInValidResults(updateResults);
        for(auto& result : updateResults){
            if(result.openentKilled){
                enemyArray.get()->at(result.opponentPosition) = nullptr;
            }
            if(result.selfKilled){
                allyArray.get()->at(result.selfPosition) = nullptr;
            }
        }

        // update enemies
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            updateResults.push_back(updateUnit(i, enemyArray.get()->at(i)));
        }

        // filter result of fights and act on it
        filterOutInValidResults(updateResults);
        for(auto& result : updateResults){
            if(result.openentKilled){
                allyArray.get()->at(result.opponentPosition) = nullptr;
            }
            if(result.selfKilled){
                enemyArray.get()->at(result.selfPosition) = nullptr;
            }
        }

        // set positions of the unit sprites
        sf::Vector2f laneStartPosition = lanePositionMap[laneID];

        sf::Vector2f drawPosition = laneStartPosition;
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            allyArray->at(i)->jumpLocationTo(drawPosition);
            drawPosition.x += 350;
        }
        
        drawPosition = laneStartPosition;
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            enemyArray->at(i)->jumpLocationTo(drawPosition);
            drawPosition.x += 350;
        }
    }

    void lane::updateEffects(){
        //for every position
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            //for every spell on that position
            for(uint_fast8_t j = 0; j < laneEffects[i].size(); j++){
                laneEffects[i][j]->update(i, j, this);
            }
        }
    }

    void lane::removeAtIndex(const int index){
        allyArray.get()->at(index) = nullptr;
        enemyArray.get()->at(index) = nullptr;
    }

    void lane::removeEffectAtIndex(const int positionIndex, const int effectIndex){
        auto toRemoveEffect = laneEffects[positionIndex][effectIndex];
        laneEffects[positionIndex][effectIndex] = laneEffects[positionIndex].back();
        laneEffects[positionIndex][laneEffects[positionIndex].size() - 1] = toRemoveEffect;
        laneEffects[positionIndex].pop_back();
    }

    void lane::removeByID(const std::string& id){
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            if(allyArray.get()->at(i)->getObjectID() == id){
                allyArray.get()->at(i) = nullptr;
            }

            if(enemyArray.get()->at(i)->getObjectID() == id){
                enemyArray.get()->at(i) = nullptr;
            }
        }

        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            for(uint_fast8_t j = 0; j < laneEffects[i].size(); j++){
                if(laneEffects[i][j]->getObjectID() == id){
                    laneEffects[i][j] = nullptr;
                }
            }
        }
    }

    std::shared_ptr<gameObject> lane::getUnitPointerByID(const std::string& id){
        for(auto& unit : *allyArray.get()){
            if(unit->getObjectID() == id){
                return unit;
            }
        }
        for(auto& unit : *enemyArray.get()){
            if(unit->getObjectID() == id){
                return unit;
            }
        }
        return nullptr;
    }

    void lane::draw(sf::RenderWindow& window){
        sf::Vector2f laneStartPosition = lanePositionMap[laneID];

        sf::Vector2f drawPosition = laneStartPosition;
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            allyArray->at(i)->jumpLocationTo(drawPosition);
            allyArray->at(i)->draw(window);

            drawPosition.x += 350;
        }
        
        drawPosition = laneStartPosition;
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            enemyArray->at(i)->jumpLocationTo(drawPosition);
            enemyArray->at(i)->draw(window);

            drawPosition.x += 350;
        }
    }
