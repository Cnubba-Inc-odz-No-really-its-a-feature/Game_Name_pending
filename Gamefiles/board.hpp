#ifndef _BOARD_HPP
#define _BOARD_HPP

#include "memory"
#include "gameObject.hpp"
#include "macrodefinitions.hpp"
#include "laneArrayContainer.hpp"

enum E_lane{
  skyLane, groundLane, trapLane  
};

struct unitUpdateResult{
    int selfPosition;
    int opponentPosition;

    bool openentKilled;
    bool selfKilled;
    bool valid;

    unitUpdateResult(bool valid, int selfPosition = 1, int opponentPosition = 1, bool oponentKilled = 1, bool selfKilled = 1):
        valid{valid},
        selfPosition{selfPosition},
        opponentPosition{opponentPosition},
        openentKilled{oponentKilled},
        selfKilled{selfKilled}
    {}


};

struct drawSprite{
    sf::Sprite sprite;
    sf::Vector2f position;

    drawSprite(){
        sprite = sf::Sprite();
        position = sf::Vector2f();
    }

    drawSprite(sf::Sprite sprite, const sf::Vector2f& position):
        sprite{sprite},
        position{position}
    {
        sprite.setPosition(position);
    }

    void update(sf::Sprite sprite, const sf::Vector2f& position){
        sprite = sprite;
        sprite.setPosition(position);
    }

    void draw(sf::RenderWindow& window){
        window.draw(sprite);
    }
};

class lane{
private:
    std::shared_ptr<int> playerHP;
    std::shared_ptr<int> enemyHP;

    std::shared_ptr<std::array<std::shared_ptr<gameObject>, LANE_SIZE>> allyArray;
    std::shared_ptr<std::array<std::shared_ptr<gameObject>, LANE_SIZE>> enemyArray;
    std::vector<std::shared_ptr<gameObject>> laneEffects[LANE_SIZE];
public:
    lane(){}
    
    lane(std::shared_ptr<int> playerHP,std::shared_ptr<int> enemyHP, laneArrayContainer& laneArrays):
        allyArray{laneArrays.allyArray},
        enemyArray{laneArrays.enemyArray},
        playerHP{playerHP},
        enemyHP{enemyHP}
    {}

    bool isIndexEmpty(const int index){
        return allyArray.get()->at(index) == nullptr && enemyArray.get()->at(index) == nullptr;
    }

    std::shared_ptr<gameObject> getUnitPointerAtIndex(const int index){
        if(allyArray.get()->at(index) == nullptr){
            return enemyArray.get()->at(index);
        }
        else{
            return allyArray.get()->at(index);
        }
    }

    void placeUnit(const int index, std::shared_ptr<gameObject> unitPointer){
        if(unitPointer->ally){
            allyArray.get()->at(index) = unitPointer;
        }
    }

    void placeEffect(const int index, std::shared_ptr<gameObject> effectPointer){
        laneEffects[index].push_back(effectPointer);
    }

    void updateLane(board* boardPointer){
        std::vector<unitUpdateResult> updateResults = {};
        for(uint_fast8_t i = LANE_SIZE -1; i >= 0; i--){
            updateResults.push_back(updateUnit(i, allyArray.get()->at(i)));
        }

        filterOutInValidResults(updateResults);
        for(auto& result : updateResults){
            if(result.openentKilled){
                enemyArray.get()->at(result.opponentPosition) = nullptr;
            }
            if(result.selfKilled){
                allyArray.get()->at(result.selfPosition) = nullptr;
            }
        }

        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            updateResults.push_back(updateUnit(i, enemyArray.get()->at(i)));
        }

        filterOutInValidResults(updateResults);
        for(auto& result : updateResults){
            if(result.openentKilled){
                allyArray.get()->at(result.opponentPosition) = nullptr;
            }
            if(result.selfKilled){
                enemyArray.get()->at(result.selfPosition) = nullptr;
            }
        }

        //for every position
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            //for every spell on that position
            for(uint_fast8_t j = 0; j < laneEffects[i].size(); j++){
                laneEffects[i][j]->update(i, j, this);
            }
        }
    }

    void filterOutInValidResults(std::vector<unitUpdateResult>& rawResults){
        std::vector<unitUpdateResult> cleanVector;
        for(const auto result : rawResults){
            if(result.valid){
                cleanVector.push_back(result);
            }
        }

        rawResults = cleanVector;
    }

    unitUpdateResult updateUnit(const int index, std::shared_ptr<gameObject> unit){
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

    unitUpdateResult fight(std::shared_ptr<gameObject> initiator, std::shared_ptr<gameObject> assaulted, const int index){
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
    
    void updateAllUnits(board* boardPointer){
        for(uint_fast8_t i = LANE_SIZE -1; i >= 0; i--){
            updateUnit(i, allyArray.get()->at(i));
        }

        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            updateUnit(i, enemyArray.get()->at(i));
        }
    }

    void updateEffects(board* boardPointer){
        //for every position
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            //for every spell on that position
            for(uint_fast8_t j = 0; j < laneEffects[i].size(); j++){
                laneEffects[i][j]->update(i, j, this);
            }
        }
    }

    void removeAtIndex(const int index){
        allyArray.get()->at(index) = nullptr;
        enemyArray.get()->at(index) = nullptr;
    }

    void removeEffectAtIndex(const int positionIndex, const int effectIndex){
        auto toRemoveEffect = laneEffects[positionIndex][effectIndex];
        laneEffects[positionIndex][effectIndex] = laneEffects[positionIndex].back();
        laneEffects[positionIndex][laneEffects[positionIndex].size() - 1] = toRemoveEffect;
        laneEffects[positionIndex].pop_back();
    }

    void removeByID(const std::string& id){
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

    std::shared_ptr<gameObject> getUnitPointerByID(const std::string& id){
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

    void draw(sf::RenderWindow& window, const sf::Vector2f& startPosition){
        drawSprite drawingSprite;
        sf::Vector2f drawPosition = startPosition;
        for(auto& unit : *allyArray.get()){
            drawingSprite.update(unit->getSprite(), drawPosition);
            drawingSprite.draw(window);

            drawPosition.x += window.getSize().x * 0.1;
        }
        
        drawPosition = startPosition;
        for(auto& unit : *enemyArray.get()){
            drawingSprite.update(unit->getSprite(), drawPosition);
            drawingSprite.draw(window);

            drawPosition.x += window.getSize().x * 0.1;
        }
    }

};


class board {
private:
    lane lanes[3];
    sf::Sprite boardSprite;
    E_lane priorityLane;

    int playerHP = 5;
    int enemyHP = 5;
public:
    board(boardLaneArraysContainer& boardContainer):
        priorityLane{E_lane::skyLane}
    {
        lanes[E_lane::skyLane] = lane(std::make_shared<int>(playerHP), std::make_shared<int>(enemyHP), boardContainer.skyLane);
        lanes[E_lane::groundLane] = lane(std::make_shared<int>(playerHP), std::make_shared<int>(enemyHP), boardContainer.groundLane);
        lanes[E_lane::trapLane] = lane(std::make_shared<int>(playerHP), std::make_shared<int>(enemyHP), boardContainer.trapLane);
    }

    board(const sf::Texture& boardTexture, boardLaneArraysContainer& boardContainer):
        boardSprite{boardTexture},
        priorityLane{E_lane::skyLane}
    {
        lanes[E_lane::skyLane] = lane(std::make_shared<int>(playerHP), std::make_shared<int>(enemyHP), boardContainer.skyLane);
        lanes[E_lane::groundLane] = lane(std::make_shared<int>(playerHP), std::make_shared<int>(enemyHP), boardContainer.groundLane);
        lanes[E_lane::trapLane] = lane(std::make_shared<int>(playerHP), std::make_shared<int>(enemyHP), boardContainer.trapLane);
    }

    void update(){
        lanes[priorityLane].updateLane(this);
        
        for(uint_fast8_t i = 0; i < 3; i++){
            if(i != priorityLane){
                lanes[i].updateLane(this);
            }
        }
    }

    void updateUnitsOnAllLanes(const int E_lane){
        for(lane& currentLane : lanes){
            currentLane.updateAllUnits(this);
        }
    }

    void updateEffectsOnAllLanes(const int E_lane){
        for(lane& currentLane : lanes){
            currentLane.updateLane(this);
        }
    }

    void updateLane(const int E_lane){
        lanes[E_lane].updateLane(this);
    }

    void updateUnitsOnLane(const int E_lane){
        lanes[E_lane].updateAllUnits(this);
    }

    void updateEffectsOnLane(const int E_lane){
        lanes[E_lane].updateEffects(this);
    }

    void placeUnit(const int E_lane, const int index, std::shared_ptr<gameObject> unitPointer){
        if(index >=0 && index < LANE_SIZE){
            lanes[E_lane].placeUnit(index, unitPointer);
        }
        else{
            std::cout << "index out of range" << std::endl;
        }
    }
    
    void placeTrapcard(const int index, std::shared_ptr<gameObject> trapcardPointer){
        if(index >=0 && index < LANE_SIZE){
            lanes[E_lane::trapLane].placeUnit(index, trapcardPointer);
        }
        else{
            std::cout << "index out of range" << std::endl;
        }
    }

    void placeEffect(const int E_lane, const int index, std::shared_ptr<gameObject> effectPointer){
        if(index >=0 && index < LANE_SIZE){
            lanes[E_lane].placeEffect(index, effectPointer);
        }
        else{
            std::cout << "index out of range" << std::endl;
        }
    }

    void castSpell(const int E_lane, const int index, std::shared_ptr<gameObject> spell){
        spell.activate(&lanes, E_lane, index);
    }

    void removeUnit(const int E_lane, const int index){
        lanes[E_lane].removeAtIndex(index);
    }

    void removeEffect(const int E_lane, const int index, const int effectIndex){
        lanes[E_lane].removeEffectAtIndex(index, effectIndex);
    }

    void removeByID(const std::string& id){
        for(lane& currentLane : lanes){
            currentLane.removeByID(id);
        }
    }

    std::shared_ptr<gameObject> getUnitPointer(const int E_lane, const int laneIndex){
        return lanes[E_lane].getUnitPointerAtIndex(laneIndex);
    }

    std::shared_ptr<gameObject> getUnitPointerByID(const std::string& id){
        std::shared_ptr<gameObject> unitPointer;

        for(auto& currentLane : lanes){
            unitPointer = currentLane.getUnitPointerByID(id);
            if(unitPointer != nullptr){
                return unitPointer;
            }
        }

        return nullptr;
    }

    bool isPositionEmpty(const int E_lane, const int index){
        return lanes[E_lane].isIndexEmpty(index);
    }

    bool isTrapCardOnPosition(const int index){
        return lanes[E_lane::trapLane].isIndexEmpty(index);
    }

    void draw(sf::RenderWindow& window){
        sf::Vector2f drawPosition = sf::Vector2f(window.getSize().x * 0.2, window.getSize().y * 0.2);
        window.draw(boardSprite);

        for(auto& currentLane : lanes){
            currentLane.draw(window, drawPosition);
            drawPosition.y += window.getSize().y *0.2;
            drawPosition.x = window.getSize().x * 0.2;
        }
    }
};

#endif