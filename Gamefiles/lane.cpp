#include "lane.hpp"
#include "functional"
    
    lane::lane(E_lane laneID, int_fast8_t &playerHP, int_fast8_t& enemyHP):
        laneID{laneID},
        playerHP{playerHP},
        enemyHP{enemyHP}
    {
        nullUnitPointer = std::make_shared<nullUnit>();
        allyArray = {nullptr, nullptr, nullptr, nullptr, nullptr};
        enemyArray = {nullptr, nullptr, nullptr, nullptr, nullptr};
        std::cout << "lane made" << std::endl;
    }

    bool lane::isIndexEmpty(const int index){
        if (index < 0)
        {
            return false;
        }
        return allyArray.at(index) == nullptr && enemyArray.at(index) == nullptr;
    }

    void lane::placeUnit(std::shared_ptr<unit> unitPointer){
        std::cout << "lane::placeUnit(" << unitPointer.get() << ")" << std::endl;
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
        allyArray = {nullptr, nullptr, nullptr, nullptr, nullptr};
        enemyArray = {nullptr, nullptr, nullptr, nullptr, nullptr};
    }

    sf::Vector2f lane::getLaneStartPosition(E_lane laneID, sf::RenderWindow& window){
        sf::Vector2u windowSize = window.getSize();
        switch(laneID){
            case E_lane::skyLane:
                return sf::Vector2f(ITERATION_DISTANCE_X *1.3, ITERATION_DISTANCE_Y * 3);
                break;
            case E_lane::groundLane:
                return sf::Vector2f(ITERATION_DISTANCE_X *1.3, ITERATION_DISTANCE_Y * 6.7);
                break;
            case E_lane::trapLane:
                return sf::Vector2f(ITERATION_DISTANCE_X *2, ITERATION_DISTANCE_Y * 4);
                break;
            default:
                return sf::Vector2f(0,0);
                break;
        }
    }

    float lane::getIterationDistanceX(sf::RenderWindow& window){
        sf::Vector2u windowSize = window.getSize();
        return ITERATION_DISTANCE_X;
    }

    void lane::draw(sf::RenderWindow& window){
        std::function<void(const std::array<std::shared_ptr<unit>, LANE_SIZE>&, const sf::Vector2f&, float, sf::RenderWindow& window)> drawArray = [&](const std::array<std::shared_ptr<unit>, LANE_SIZE>& array, const sf::Vector2f& laneStartPosition, float positionIterationDistanceX, sf::RenderWindow& window)->void{
            sf::Vector2f drawPosition = laneStartPosition;
            for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
                if(array[i] != nullptr){
                    // std::cout << "drawPosition: " << drawPosition.x << "," << drawPosition.y << std::endl;
                    array[i]->setPosition(drawPosition);
                    // std::cout << "unitPosition: " << array[i]->getSprite().getPosition().x << "," << array[i]->getSprite().getPosition().x << std::endl;
                    array[i]->draw(window);
                    drawPosition.x += positionIterationDistanceX * i;
                }
            }
        };

        sf::Vector2f laneStartPosition = getLaneStartPosition(laneID, window);
        float positionIterationDistanceX = getIterationDistanceX(window);

        drawArray(allyArray, laneStartPosition, positionIterationDistanceX, window);
        drawArray(enemyArray, laneStartPosition, positionIterationDistanceX, window);
    }

    void lane::updateLane(){
        // std::cout << "updating lane: " << laneID << "     enemyHP: " << int(enemyHP) << std::endl;
        uint_fast8_t maxLaneIndex = LANE_SIZE - 1;

        // std::cout << "updateLane last index: " << allyArray[6] << std::endl;

        // update allies
        for(int_fast8_t i = maxLaneIndex; i >= 0; i--){
            if(allyArray[i] != nullptr){
                updateUnit(i, allyArray[i]);
            }
        }

        // update enemies
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            if(enemyArray[i] != nullptr){
                updateUnit(i, enemyArray[i]);
            }
        }
    }

    void lane::updateUnit(const int index, std::shared_ptr<unit> toUpdateUnit){

        std::function<void(int, int, std::array<std::shared_ptr<unit>, LANE_SIZE>&)> moveUnit = [&](int index, int nextIndex, std::array<std::shared_ptr<unit>, LANE_SIZE>& array)->void{
            array[nextIndex] = array[index];
            array[index] = nullptr;
        };

        std::function<void(std::array<std::shared_ptr<unit>, LANE_SIZE>&, std::array<std::shared_ptr<unit>, LANE_SIZE>&, const unitUpdateResult&)> handleCombatResult = 
        [&](std::array<std::shared_ptr<unit>, LANE_SIZE>& selfArray, std::array<std::shared_ptr<unit>, LANE_SIZE>& opponentArray, const unitUpdateResult& result)->void{
            // std::cout << "removing dead units" << std::endl;

            if(result.openentKilled){
                opponentArray[result.opponentPosition] = nullptr;
            }
            if(result.selfKilled){
                selfArray[result.selfPosition] = nullptr;
            }
            if(result.openentKilled && !result.selfKilled){
                selfArray[index + 1] = allyArray[index];
                selfArray[index] = nullptr;
            }
            
        };

        std::cout << "updateUnit(" << toUpdateUnit << ")" << "at index: " << int(index);
        if(toUpdateUnit == nullptr){
            std::cout << "nullptr found" << std::endl;
        }

        if(toUpdateUnit->isAlly()){
            int nextIndex = index + 1;
            if(nextIndex < LANE_SIZE && isIndexEmpty(nextIndex)){
                    std::cout << "|-------------> move" << std::endl;
                moveUnit(index, nextIndex, allyArray);
                return;
            }
            else if(index == 0){
                    std::cout << "|-------------> attack opponent summoner" << std::endl;
                enemyHP -= toUpdateUnit->getDamage();
                return;
            }
            else if(nextIndex < LANE_SIZE && !isIndexEmpty(nextIndex) && enemyArray[nextIndex] != nullptr){
                    std::cout << "|-------------> fight" << std::endl;
                unitUpdateResult result = fight(toUpdateUnit, enemyArray.at(nextIndex), index);
                handleCombatResult(allyArray, enemyArray, result);
                return;
            }
                    std::cout << "|-------------> do nothing" << std::endl;
        }
        else
            {
            int nextIndex = index - 1;
            if(nextIndex < LANE_SIZE && isIndexEmpty(nextIndex)){
                    std::cout << "|-------------> move" << std::endl;
                moveUnit(index, nextIndex, enemyArray);
                return;
            }
            else if(index == LANE_SIZE - 1){
                    std::cout << "|-------------> attack opponent summoner" << std::endl;
                playerHP -= toUpdateUnit->getDamage();
                return;
            }
            else if(nextIndex < LANE_SIZE && !isIndexEmpty(nextIndex) && enemyArray[nextIndex] != nullptr){
                    std::cout << "|-------------> fight" << std::endl;
                unitUpdateResult result = fight(toUpdateUnit, allyArray.at(nextIndex), index);
                handleCombatResult(enemyArray, allyArray, result);
                return;
            }
                    std::cout << "|-------------> do nothing" << std::endl;
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

    
