#ifndef _BOARD_HPP
#define _BOARD_HPP

#include "memory"
#include "gameObject.hpp"

#define LANE_SIZE 7

enum E_lane{
  skyLane, groundLane, trapLane  
};

struct unitUpdateResult{
    int position;
    bool ally;
    bool openentKilled;
    bool valid;

    unitUpdateResult(bool valid, int position = 1, bool ally = -1, bool oponentKilled = -1):
        position{position},
        ally{ally},
        openentKilled{oponentKilled},
        valid{valid}
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
    std::shared_ptr<gameObject> laneArray[LANE_SIZE];
    std::shared_ptr<gameObject> allyArray[LANE_SIZE];
    std::shared_ptr<gameObject> enemyArray[LANE_SIZE];
    std::vector<std::shared_ptr<gameObject>> laneEffects[LANE_SIZE];
public:
    lane():
        laneArray{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
    {}

    bool isIndexEmpty(const int index){
        return allyArray[index] == nullptr && enemyArray[index] == nullptr;
    }

    std::shared_ptr<gameObject> getUnitPointerAtIndex(const int index){
        if(allyArray[index] == nullptr){
            return enemyArray[index];
        }
        else{
            return allyArray[index];
        }
    }

    void placeUnit(const int index, std::shared_ptr<gameObject> unitPointer){
        if(unitPointer->ally){
            allyArray[index] = unitPointer;
        }
    }

    void placeEffect(const int index, std::shared_ptr<gameObject> effectPointer){
        laneEffects[index].push_back(effectPointer);
    }

    void updateLane(board* boardPointer){
        std::vector<unitUpdateResult> updateResults = {};
        for(uint_fast8_t i = LANE_SIZE -1; i >= 0; i--){
            updateResults.push_back(updateUnit(i, allyArray[i]));
        }

        filterOutInValidResults(updateResults);
        for(auto& result : updateResults){
            if(result.openentKilled){
                enemyArray[result.position] = nullptr;
            }
        }

        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            updateResults.push_back(updateUnit(i, enemyArray[i]));
        }

        filterOutInValidResults(updateResults);
        for(auto& result : updateResults){
            if(result.openentKilled){
                allyArray[result.position] = nullptr;
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

        rawResults = cleanVector
    }

    unitUpdateResult updateUnit(const int index, std::shared_ptr<gameObject> unit){
        if(unit->ally){
            if(index + 1 < LANE_SIZE && isIndexEmpty(index + 1)){
                allyArray[index + 1] = unit;
                allyArray[index] = nullptr;
            }
            else if(index == LANE_SIZE - 1){
                EnemySummoner.takeDamage(unit.getDamage());
            }
            else if(index + 1 < LANE_SIZE){
                unitUpdateResult result = fight(unit, enemyArray[index + 1]);

                if(result.openentKilled){
                    allyArray[index + 1] = unit;
                    allyArray[index] = nullptr;
                }

                return result
            }

                return unitUpdateResult(false);
        }
        else{
            if(index - 1 > 0 && isIndexEmpty(index - 1)){
                enemyArray[index - 1] = unit;
                enemyArray[index] = nullptr;
            }
            else if(index == 0){
                playerSummoner.takeDamage(unit.getDamage());
            }
            else if(index > 0){
                unitUpdateResult result = fight(unit, allyArray[index - 1]);

                if(result.openentKilled){
                    enemyArray[index - 1] = unit;
                    enemyArray[index] = nullptr;
                }

                return result
            }
            
            return unitUpdateResult(false);
        }
    }
    
    void updateAllUnits(board* boardPointer){
        for(uint_fast8_t i = LANE_SIZE -1; i >= 0; i--){
            updateUnit(i, allyArray[i]);
        }

        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            updateUnit(i, enemyArray[i]);
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
        laneArray[index] = nullptr;
        enemyArray[index] = nullptr;
    }

    void removeEffectAtIndex(const int positionIndex, const int effectIndex){
        auto toRemoveEffect = laneEffects[positionIndex][effectIndex];
        laneEffects[positionIndex][effectIndex] = laneEffects[positionIndex].back();
        laneEffects[positionIndex][laneEffects[positionIndex].size() - 1] = toRemoveEffect;
        laneEffects[positionIndex].pop_back();
    }

    void removeByID(const std::string& id){
        for(uint_fast8_t i = 0; i < LANE_SIZE; i++){
            if(allyArray[i]->getObjectID() == id){
                allyArray[i] = nullptr;
            }

            if(enemyArray[i]->getObjectID() == id){
                enemyArray[i] = nullptr;
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

    void draw(sf::RenderWindow& window, const sf::Vector2f& startPosition){
        drawSprite drawingSprite;
        sf::Vector2f drawPosition = startPosition;
        for(auto& unit : laneArray){
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
public:
    board(const sf::Texture& boardTexture):
        lanes{lane(), lane(), lane()},
        boardSprite{boardTexture},
        priorityLane{E_lane::skyLane}
    {}

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

    void placeUnit(const int E_lane, const int laneIndex, std::shared_ptr<gameObject> unitPointer){
        lanes[E_lane].placeUnit(laneIndex, unitPointer);
    }
    
    void placeTrapcard(const int index, std::shared_ptr<gameObject> trapcardPointer){
        lanes[E_lane::trapLane].placeUnit(index, trapcardPointer);
    }

    void placeEffect(const int E_lane, const int index, std::shared_ptr<gameObject> effectPointer){
        lanes[E_lane].placeEffect(index, effectPointer);
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