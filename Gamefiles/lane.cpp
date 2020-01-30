#include "lane.hpp"
#include "functional"
    
    lane::lane(E_lane laneID, int &playerHP, int& enemyHP):
        laneID{laneID},
        playerHP{playerHP},
        enemyHP{enemyHP}
    {
        nullUnitPointer = std::make_shared<nullUnit>();
        allyArray.fill(nullptr);
        enemyArray.fill(nullptr);
    }

    bool lane::isIndexEmpty(const int index){
        if (index < 0 || index >= LANE_SIZE)
        {
            return false;
        }
        return allyArray.at(index) == nullptr && enemyArray.at(index) == nullptr;
    }

    void lane::placeUnit(std::shared_ptr<unit> unitPointer){
        if(unitPointer != nullptr){
            if(unitPointer->isAlly()){
                allyArray[0] = unitPointer; 
            }
            else{
                enemyArray[LANE_SIZE - 1] = unitPointer;
            }
        }
    }

    void lane::reset(){
        allyArray.fill(nullptr);
        allyArray.fill(nullptr);
        std::cout << "lane reset done" << std::endl;
    }

    sf::Vector2f lane::getLaneStartPosition(E_lane laneID, sf::RenderWindow& window){
        sf::Vector2u windowSize = window.getSize();
        switch(laneID){
            case E_lane::skyLane:
                return sf::Vector2f(ITERATION_DISTANCE_X *1.4, ITERATION_DISTANCE_Y * 4);
                break;
            case E_lane::groundLane:
                return sf::Vector2f(ITERATION_DISTANCE_X *1.4, ITERATION_DISTANCE_Y * 6.7);
                break;
            case E_lane::trapLane:
                return sf::Vector2f(ITERATION_DISTANCE_X *1.4, ITERATION_DISTANCE_Y * 4);
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
        std::function<void(const std::array<std::shared_ptr<unit>, LANE_SIZE>&, const sf::Vector2f&, float, sf::RenderWindow& window)> drawArray = 
        [&](const std::array<std::shared_ptr<unit>, LANE_SIZE>& array, const sf::Vector2f& laneStartPosition, float positionIterationDistanceX, sf::RenderWindow& window)->void{
            sf::Vector2f drawPosition = laneStartPosition;
            for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
                if(array[i] != nullptr){
                    drawPosition.x = positionIterationDistanceX * i + laneStartPosition.x;
                    array[i]->setPosition(drawPosition);
                    array[i]->update();
                    array[i]->draw(window);
                }
            }
        };

        sf::Vector2f laneStartPosition = getLaneStartPosition(laneID, window);
        float positionIterationDistanceX = getIterationDistanceX(window);
        drawArray(allyArray, laneStartPosition, positionIterationDistanceX, window);
        drawArray(enemyArray, laneStartPosition, positionIterationDistanceX, window);
    }

    void lane::updateAllyLane(){
        uint_fast8_t maxLaneIndex = LANE_SIZE - 1;
        for(int_fast8_t i = maxLaneIndex; i >= 0; i--){
            if(allyArray[i] != nullptr){
                updateUnit(i, allyArray[i]);
            }
        }
    }

    void lane::updateEnemyLane(){
        uint_fast8_t maxLaneIndex = LANE_SIZE - 1;
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
        if(toUpdateUnit == nullptr){
        }

        if(toUpdateUnit->isAlly()){
            int nextIndex = index + 1;
            if(isIndexEmpty(nextIndex)){
                moveUnit(index, nextIndex, allyArray);
                if(nextIndex == LANE_SIZE - 1){
                    enemyHP -= toUpdateUnit->getDamage();
                    allyArray[LANE_SIZE - 1] = nullptr;
                }
                return;
            }
        }
        else
            {
            int nextIndex = index - 1;
            if(isIndexEmpty(nextIndex)){
                moveUnit(index, nextIndex, enemyArray);
                if(nextIndex == 0){
                    playerHP -= toUpdateUnit->getDamage();
                    enemyArray[0] = nullptr;
                }
            }
        }
    }
    

    void lane::fightPhase(){

        for(uint_fast8_t allyIndex = 0; allyIndex < LANE_SIZE - 1; allyIndex++){

            if(allyArray[allyIndex] != nullptr && enemyArray[allyIndex + 1] != nullptr){
                combatResult fightResult = fight(allyArray[allyIndex], enemyArray[allyIndex + 1], allyIndex);

                if(fightResult.opponentKilled){
                    enemyArray[fightResult.opponentPosition] = nullptr;
                }
                if(fightResult.selfKilled){
                    allyArray[fightResult.selfPosition] = nullptr;
                }
            }
        }
    }

    combatResult lane::fight(std::shared_ptr<unit> initiator, std::shared_ptr<unit> assaulted, const int index){
        assaulted->takeDamage(initiator->getDamage());
        initiator->takeDamage(assaulted->getDamage());

        int selfPosition = index;
        int opponentPosition = index + 1;

        bool selfKilled = initiator->checkIsDead();
        bool opponentKilled = assaulted->checkIsDead();

        return combatResult(true, selfPosition, opponentPosition ,opponentKilled, selfKilled);
    }

    void lane::print_array(){
        for(int x = 0; x < 4; x++){
        }
    }
