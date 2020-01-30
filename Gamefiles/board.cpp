#include "board.hpp"
#include <iostream>
// board::board(){}

board::board(int_fast8_t & playerHP, int_fast8_t & enemyHP, int & playerMana, int & enemyMana ):
        lanes({
            lane(E_lane::skyLane, playerHP, enemyHP),
            lane(E_lane::groundLane, playerHP, enemyHP),
            lane(E_lane::trapLane, playerHP, enemyHP)
        }),
        priorityLane{E_lane::groundLane},
        playerHP{playerHP},
        enemyHP{enemyHP},
        playerMana{playerMana},
        enemyMana{enemyMana}
    {

        mana_healthFont.loadFromFile("gameAssets/cardAssets/cardFont.otf");
        playerManaText.setFont(mana_healthFont);
        playerHealthText.setFont(mana_healthFont);
        playerManaText.setPosition(30, 600);
        playerHealthText.setPosition(30, 700);
        playerManaText.setString("ManaPool: " + std::to_string(playerMana));
        playerHealthText.setString("HP: " + std::to_string(playerHP));
        playerManaText.setFillColor(sf::Color::Blue);
        playerHealthText.setFillColor(sf::Color::Red);
    
    }

    bool board::getSkyOpen(){
        return lanes[E_lane::skyLane].isIndexEmpty(0);
    }

    bool board::getGroundOpen(){
        return lanes[E_lane::groundLane].isIndexEmpty(0);
    }

    // int_fast8_t board::GetHP(std::string who){
    //     if(who == "player"){
    //         return playerHP;
    //     }
    //     else{
    //         return enemyHP;
    //     }
    // }

    void board::updateAlly(){
        lanes[priorityLane].updateAllyLane();
        
        for(uint_fast8_t i = 0; i < 3; i++){
            if(i != priorityLane){
                lanes[i].updateAllyLane();
            }
        }
        playerManaText.setString("ManaPool: " + std::to_string(playerMana));
        playerHealthText.setString("HP: " + std::to_string(playerHP));
    }

    void board::updateEnemy(){
        lanes[priorityLane].updateEnemyLane();
        
        for(uint_fast8_t i = 0; i < 3; i++){
            if(i != priorityLane){
                lanes[i].updateEnemyLane();
            }
        }
    }

    bool board::placeUnit(std::shared_ptr<unit> unitPointer){
        std::cout << "placing unit on board via board on lane: " << int(unitPointer->getLaneType()) << std::endl;
        std::cout << "unit cost: " << unitPointer->mana << std::endl;
        if(lanes[unitPointer->getLaneType()].isIndexEmpty(0)){
            playerManaText.setString("ManaPool: " + std::to_string(playerMana));
            lanes[unitPointer->getLaneType()].placeUnit(unitPointer);
            std::cout << "board::placeUnit() success" << std::endl;
            return true;
        }
        return false;
    }

    bool board::isPositionEmpty(const int E_lane, const int index){
        return lanes[E_lane].isIndexEmpty(index);
    }

    void board::draw(sf::RenderWindow& window){
        for(auto& currentLane : lanes){
            currentLane.draw(window);
        }

        window.draw(playerManaText);
        window.draw(playerHealthText);
    }

    void board::reset(){
        for(auto& lane : lanes){
            lane.reset();
        }
        playerManaText.setString("ManaPool: " + std::to_string(playerMana));
        playerHealthText.setString("HP: " + std::to_string(playerHP));
    }

