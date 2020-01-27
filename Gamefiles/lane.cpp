#include "lane.hpp"
#include "functional"
    
    lane::lane(E_lane laneID, int_fast8_t &playerHP, int_fast8_t& enemyHP):
        laneID{laneID},
        playerHP{playerHP},
        enemyHP{enemyHP}
    {
        nullUnitPointer = std::make_shared<nullUnit>();
        allyArray = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
        enemyArray = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
        std::cout << "lane made" << std::endl;
    }

    bool lane::isIndexEmpty(const int index){
        return allyArray.at(index) == nullptr && enemyArray.at(index) == nullptr;
    }

    void lane::placeUnit(std::shared_ptr<unit> unitPointer){
        std::cout << "lane::placeUnit()" << std::endl;
        if(unitPointer->isAlly()){
            allyArray[0] = unitPointer;
        }
    }

    void lane::reset(){
        allyArray = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
        enemyArray = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    }

    std::function<void(std::array<std::shared_ptr<unit>, LANE_SIZE>&, const sf::Vector2f&)> drawArray = [](std::array<std::shared_ptr<unit>, LANE_SIZE>& array, const sf::Vector2f& laneStartPosition)->void{
        sf::Vector2f drawPosition = laneStartPosition;
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            if(array[i] != nullptr){
                array[i]->jumpLocationTo(drawPosition);
                drawPosition.x += 350;
            }
        }
    };

    void lane::updateLane(){
        std::cout << "entered updateLane()" << std::endl;
        std::cout << "enemyHP: " << int(enemyHP) << std::endl;
        std::vector<unitUpdateResult> updateResults = {};
        uint_fast8_t maxLaneIndex = LANE_SIZE - 1;

        std::function<void(std::vector<unitUpdateResult>&)> removeDeadUnitsFromResults = [&](std::vector<unitUpdateResult>& results)->void{
            std::cout << "removing dead units" << std::endl;
            // filterOutInValidResults(results);
            for(auto& result : results){
                if(result.valid == false){
                    continue;
                }

                if(result.isAlly){
                    if(result.openentKilled){
                        enemyArray[result.opponentPosition] = nullptr;
                    }
                    if(result.selfKilled){
                        allyArray[result.selfPosition] = nullptr;
                    }
                }
                else{
                    if(result.openentKilled){
                        allyArray.at(result.opponentPosition) = nullptr;
                    }
                    if(result.selfKilled){
                        enemyArray.at(result.selfPosition) = nullptr;
                    }
                }
            }
            results = {};
        };

        // update allies
        std::cout << "hey" <<std::endl;
        for(int_fast8_t i = maxLaneIndex; i >= 0; i--){
            std::cout << "pre if" << std::endl;
            if(allyArray[i] != nullptr){
                std::cout << "no nullptr" << int(i) << " " << allyArray[i]->getLaneType() << std::endl;  
                updateResults.push_back(updateUnit(i, allyArray.at(i)));
            }
        }
        std::cout << "pre-removing dead units." << std::endl;
        removeDeadUnitsFromResults(updateResults);

        // update enemies
        std::cout << "hey2" << std::endl;
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            if(enemyArray[i] != nullptr){
                updateResults.push_back(updateUnit(i, enemyArray.at(i)));
            }
        }
        removeDeadUnitsFromResults(updateResults);

        // set drawingPosition for the units
        std::cout << "getting laneStartPosition" << std::endl;
        sf::Vector2f laneStartPosition = lanePositionMap[laneID];

        std::cout << "drawing allies" << std::endl;
        drawArray(allyArray, laneStartPosition);
        
        std::cout << "drawing enemies" << std::endl;
        drawArray(enemyArray, laneStartPosition);
    }

    unitUpdateResult lane::updateUnit(const int index, std::shared_ptr<unit> toUpdateUnit){
        std::cout << "updateUnit()" << std::endl;
        if(toUpdateUnit == nullptr){
            std::cout << "nullptr found" << std::endl;
            return unitUpdateResult(false);
        }

        if(toUpdateUnit->isAlly()){
            int nextIndex = index + 1;
            if(nextIndex < LANE_SIZE && isIndexEmpty(nextIndex)){
                allyArray.at(nextIndex) = toUpdateUnit;
                allyArray.at(index) = nullptr;
            }
            else if(index == LANE_SIZE - 1){
                enemyHP -= toUpdateUnit->getDamage();
            }
            else if(nextIndex < LANE_SIZE && enemyArray[nextIndex] != nullptr){
                unitUpdateResult result = fight(toUpdateUnit, enemyArray.at(nextIndex), index);

                if(result.openentKilled && !result.selfKilled){
                    allyArray.at(nextIndex) = toUpdateUnit;
                    allyArray.at(index) = nullptr;
                }

                return result;
            }

                return unitUpdateResult(false);
        }
        else{
            int nextIndex = index - 1;
            if(nextIndex > LANE_SIZE && isIndexEmpty(nextIndex)){
                enemyArray.at(nextIndex) = toUpdateUnit;
                enemyArray.at(index) = nullptr;
            }
            else if(index == LANE_SIZE - 1){
                enemyHP -= toUpdateUnit->getDamage();
            }
            else if(nextIndex < LANE_SIZE && allyArray[nextIndex] != nullptr){
                unitUpdateResult result = fight(toUpdateUnit, enemyArray.at(nextIndex), index);

                if(result.openentKilled && !result.selfKilled){
                    enemyArray.at(nextIndex) = toUpdateUnit;
                    enemyArray.at(index) = nullptr;
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

        return unitUpdateResult(true, selfPosition, opponentPosition ,opponentKilled, selfKilled, initiator->isAlly());
    }

    void lane::draw(sf::RenderWindow& window){
        std::cout << "drawing board via fightControl" << std::endl;
        sf::Vector2f laneStartPosition = lanePositionMap[laneID];
        drawArray(allyArray, laneStartPosition);
        drawArray(enemyArray, laneStartPosition);
    }
