#ifndef _FIGHT_CONTROLLER_HPP
#define _FIGHT_CONTROLLER_HPP

//#include "card.hpp"
#include "board.hpp"
#include "objectStorage.hpp"

class fightController{
private:
    board gameBoard;
    int playerHP;
    int enemyHP;
    int enemyMana;
    int currentPlayerMana;
    fightHand& cardHand;
    sf::Texture endTurnButtonTexture;
    sf::Sprite endTurnButton;
    sf::RenderWindow& gameWindow;
    objectStorage & storage;
    uint64_t lastTurnEndTime;
    bool active = false; 
    uint64_t lastInput;
    int lastPhase;
    std::shared_ptr<bool> allowedToEnd;
public:
    fightController(fightHand& cardHand, objectStorage & storage): 
        playerHP{MAX_HP},
        enemyHP{MAX_HP},
        currentPlayerMana{1},
        enemyMana{1},
        gameBoard(playerHP, enemyHP, playerMana, enemyMana),
        cardHand(cardHand),
        gameWindow(gameWindow),
        storage(storage),
        allowedToEnd(nullptr)
    {
        endTurnButtonTexture.loadFromFile("gameAssets/doneButton.png");
        endTurnButton.setTexture(endTurnButtonTexture);
        endTurnButton.setPosition(sf::Vector2f(10,900));
        endTurnButton.setScale(sf::Vector2f(0.25, 0.25));
        initFight();
        lastTurnEndTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }

    int playerMana; 

    void initFight(){
        playerHP = MAX_HP;
        enemyHP = MAX_HP;

        playerMana =  1;
        enemyMana = 1;
        currentPlayerMana = 1;
        gameBoard.reset();
        cardHand.newFight();
        cardHand.newHand();

    }

    bool getActive(){
        return active;
    }

    bool getSkyOpen(){
        return gameBoard.getSkyOpen();
    }

    bool getGroundOpen(){
        return gameBoard.getGroundOpen();
    }

    void setAllowedToEnd(std::shared_ptr<bool> NewAllowedToEnd){
        allowedToEnd = NewAllowedToEnd;
    }

    void nextTurn(int phase){
        std::vector<std::shared_ptr<unit>> newEnemyUnits;
        int currentPhase;

        if(phase == 0){
            uint_fast64_t currentTime =  std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            if(currentTime > lastInput + BATTLE_PHASE_DELAY){
                currentPhase = lastPhase + 1;
            }
            //update and track time, and update currentphase accordingly
        }
        else{
            currentPhase = phase;
        }

        switch(currentPhase){
            case 1:
            
                lastInput = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                lastPhase = currentPhase;
                active = true;
                if(currentPlayerMana < 10){
                    currentPlayerMana++;
                }
                playerMana = currentPlayerMana;
                enemyMana = currentPlayerMana;
                gameBoard.updateAlly();
                break;

            case 2:
                lastInput = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                lastPhase = currentPhase;
                newEnemyUnits = storage.fightEnemy.generateEnemyUnits(getSkyOpen(), getGroundOpen());
                std::for_each(newEnemyUnits.begin(), newEnemyUnits.end(), [this](auto&i){placeUnitOnBoard(i);});
                break;

            case 3:
                lastInput = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                lastPhase = currentPhase;
                gameBoard.updateEnemy();
                break;

            case 4:
                lastInput = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                lastPhase = currentPhase;
                gameBoard.fightPhase();
                break;

            case 5:
                lastInput = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                lastPhase = 0;
                cardHand.newHand();

                if(enemyHP <= 0){
                    storage.factorNewGameState("rewardroom.txt");
                    storage.setActive("rewardroom.txt");
                    std::cout << "reset" << std::endl;
                    initFight();
                } 
                if(playerHP <= 0){
                    storage.setActive(storage.getReturnTarget());

                    std::cout << playerMana << " " << enemyMana << std::endl; 
                    initFight();
                }
                active = false;
                *allowedToEnd.get() = true;
                break;

            default:
                break;
        }

    }

    bool placeUnitOnBoard(std::shared_ptr<unit> unitPointer){
        bool success = gameBoard.placeUnit(unitPointer);
        return success;
    }

    bool isDoneButtonPressed(sf::Vector2i mousePosI){
        sf::Vector2f mousePosF(float(mousePosI.x), float(mousePosI.y));
        return endTurnButton.getGlobalBounds().contains(mousePosF);
    }

    void draw(sf::RenderWindow& window){
        gameBoard.draw(window);
        window.draw(endTurnButton);
        storage.fightEnemy.draw(window);
        
    }

    

};

#endif