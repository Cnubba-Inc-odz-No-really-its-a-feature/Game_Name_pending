#ifndef _FIGHT_CONTROLLER_HPP
#define _FIGHT_CONTROLLER_HPP

//#include "card.hpp"
#include "board.hpp"
#include "objectStorage.hpp"
#include "combatEnemy.hpp"
enum class E_fightState{
    win,
    loss,
    draw,
    inCombat
};

class fightController{
private:
    board gameBoard;
    int playerHP;
    int enemyHP;
    E_fightState fightState;
    int enemyMana;
    int currentPlayerMana;
    fightHand& cardHand;
    sf::Texture endTurnButtonTexture;
    sf::Sprite endTurnButton;
    combatEnemy fightEnemy;
    objectStorage & storage;
    
public:
    fightController(fightHand& cardHand, objectStorage & storage): 
        playerHP{MAX_HP},
        enemyHP{MAX_HP},
        currentPlayerMana{1},
        enemyMana{1},
        gameBoard(playerHP, enemyHP, playerMana, enemyMana),
        cardHand(cardHand),
        fightEnemy(std::string("gameAssets/skeleton.png")),
        storage(storage)
    {
        endTurnButtonTexture.loadFromFile("gameAssets/doneButton.png");
        endTurnButton.setTexture(endTurnButtonTexture);
        endTurnButton.setPosition(sf::Vector2f(10,900));
        endTurnButton.setScale(sf::Vector2f(0.25, 0.25));
        initFight();
        
    }

    int playerMana; 

    void initFight(){
        std::cout<<"initiating fight"<<std::endl;
        playerHP = MAX_HP;
        enemyHP = MAX_HP;
        playerMana =  currentPlayerMana;
        enemyMana = currentPlayerMana;
        gameBoard.reset();
        cardHand.newFight();
       // cardHand.newHand();
        std::cout<<"fight initiated"<<std::endl;

    }

    bool getSkyOpen(){
        return gameBoard.getSkyOpen();
    }

    bool getGroundOpen(){
        return gameBoard.getGroundOpen();
    }

    void nextTurn(){
        std::cout << "nextTurn()________________________________________________________________________" << std::endl;
        if(currentPlayerMana < MAX_MANA) currentPlayerMana++;
        playerMana = currentPlayerMana;
        enemyMana = currentPlayerMana;
        if(enemyHP <= 0){
            // storage.allVectors.erase("rewardroom.txt");
            storage.setActive("rewardroom.txt");
            return;
        } 
        if(playerHP <= 0){
            storage.setActive(storage.getReturnTarget());
            return;
        }
        gameBoard.updateAlly();
        std::vector<std::shared_ptr<unit>> newEnemyUnits = fightEnemy.generateEnemyUnits();
        std::for_each(newEnemyUnits.begin(), newEnemyUnits.end(), [this](auto&i){placeUnitOnBoard(i);});
        gameBoard.updateEnemy();
        
        cardHand.newHand();
        std::cout << "playerMana: " << playerMana << std::endl;
    }

    bool placeUnitOnBoard(std::shared_ptr<unit> unitPointer){
        std::cout << "placing on board via fightController" << std::endl;
        bool success = gameBoard.placeUnit(unitPointer);
        std::cout << "unitPlacement: " << success << std::endl;
        return success;
    }

    bool isDoneButtonPressed(sf::Vector2i mousePosI){
        sf::Vector2f mousePosF(float(mousePosI.x), float(mousePosI.y));
        return endTurnButton.getGlobalBounds().contains(mousePosF);
    }

    void draw(sf::RenderWindow& window){
        gameBoard.draw(window);
        window.draw(endTurnButton);
        //fightEnemy.draw(window);
        
    }

    

};

#endif