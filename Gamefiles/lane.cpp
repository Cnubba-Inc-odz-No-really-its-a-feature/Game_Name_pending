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
        if(unitPointer != nullptr){
            if(unitPointer->isAlly()){
                allyArray[0] = unitPointer;
                std::cout << allyArray[0];
            }
            else{
                enemyArray[0] = unitPointer;
            }
        }
    }

    void lane::reset(){
        allyArray = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
        enemyArray = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    }


    void lane::updateLane(){
        std::cout << "____________________enemyHP: " << int(enemyHP) << std::endl;
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
        for(int_fast8_t i = maxLaneIndex; i >= 0; i--){\
            if(allyArray[i] != nullptr){
                std::cout << "no nullptr" << int(i) << " " << allyArray[i]->getLaneType() << std::endl;  
                updateResults.push_back(updateUnit(i, allyArray.at(i)));
            }
        }
        removeDeadUnitsFromResults(updateResults);

        // update enemies
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            if(enemyArray[i] != nullptr){
                updateResults.push_back(updateUnit(i, enemyArray.at(i)));
            }
        }
        removeDeadUnitsFromResults(updateResults);
    }

    unitUpdateResult lane::updateUnit(const int index, std::shared_ptr<unit> toUpdateUnit){
        std::cout << "updateUnit()" << std::endl;
        if(toUpdateUnit == nullptr){
            std::cout << "nullptr found" << std::endl;
            return unitUpdateResult(false);
        }

        if(toUpdateUnit->isAlly()){
            std::cout << toUpdateUnit->getDamage() << std::endl;
            int nextIndex = index + 1;
            if(nextIndex < LANE_SIZE && isIndexEmpty(nextIndex)){
                std::cout << "              walk" << std::endl;
                allyArray[nextIndex] = allyArray[index];
                allyArray[index] = nullptr;
            }
            else if(index == LANE_SIZE - 1){
                std::cout << "              attack opponent summoner" << std::endl;
                enemyHP -= toUpdateUnit->getDamage();
            }
            else if(nextIndex < LANE_SIZE && !isIndexEmpty(nextIndex) && enemyArray[nextIndex] != nullptr){
                std::cout << "              fight" << std::endl;
                unitUpdateResult result = fight(toUpdateUnit, enemyArray.at(nextIndex), index);

                if(result.openentKilled && !result.selfKilled){
                    allyArray[nextIndex] = allyArray[index];
                    allyArray[index] = nullptr;
                }

                return result;
            }
                std::cout << "              do nothing" << std::endl;

                return unitUpdateResult(false);
        }
        else{
            int nextIndex = index - 1;
            if(nextIndex > 0 && isIndexEmpty(nextIndex)){
                enemyArray[nextIndex] = enemyArray[0];
                enemyArray[index] = nullptr;
            }
            else if(index == 0){
                playerHP -= toUpdateUnit->getDamage();
            }
            else if(nextIndex > 0 && !isIndexEmpty(nextIndex) && allyArray[nextIndex] != nullptr){
                unitUpdateResult result = fight(toUpdateUnit, allyArray[nextIndex], index);

                if(result.openentKilled && !result.selfKilled){
                    enemyArray[nextIndex] = enemyArray[0];
                    enemyArray[index] = nullptr;
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

    std::function<void(const std::array<std::shared_ptr<unit>, LANE_SIZE>&, const sf::Vector2f&, sf::RenderWindow& window)> drawArray = [&](const std::array<std::shared_ptr<unit>, LANE_SIZE>& array, const sf::Vector2f& laneStartPosition, sf::RenderWindow& window)->void{
        sf::Vector2f drawPosition = laneStartPosition;
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            if(array[i] != nullptr){
                std::cout << "drawing unit on index: " << i << std::endl;
                array[i]->jumpLocationTo(drawPosition);
                array[i]->draw(window);
                drawPosition.x += 350;
            }
        }
    };

    void lane::draw(sf::RenderWindow& window){
        sf::Vector2f laneStartPosition = lanePositionMap[laneID];

        // sf::Vector2f drawPosition = laneStartPosition;
        // std::cout << "drawArray lambda called" << std::endl;
        // for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
        //     std::cout << "iterating for-loop" << std::endl;
        //     std::cout << allyArray[i] << std::endl;
        //     if(allyArray[i] != nullptr){
        //         std::cout << "drawing unit on index: " << i << std::endl;
        //         allyArray[i]->jumpLocationTo(drawPosition);
        //         allyArray[i]->draw(window);
        //         drawPosition.x += 350;
        //     }
        // }

        // drawPosition = laneStartPosition;
        // std::cout << "drawArray lambda called" << std::endl;
        // for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
        //     if(enemyArray[i] != nullptr){
        //         std::cout << "drawing unit on index: " << i << std::endl;
        //         enemyArray[i]->jumpLocationTo(drawPosition);
        //         enemyArray[i]->draw(window);
        //         drawPosition.x += 350;
        //     }
        // }

        drawArray(allyArray, laneStartPosition, window);
        drawArray(enemyArray, laneStartPosition, window);
    }
