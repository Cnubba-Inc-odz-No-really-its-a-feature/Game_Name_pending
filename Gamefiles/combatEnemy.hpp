#ifndef _COMBATENEMY_HPP
#define _COMBATENEMY_HPP
#include "card.hpp"

class combatEnemy{
private:
    sf::Texture combatEnemyTexture;
    sf::Sprite combatEnemySprite;

public:
    combatEnemy(std::string textureFileName){
        combatEnemyTexture.loadFromFile(textureFileName);
        combatEnemySprite.setTexture(combatEnemyTexture);
        combatEnemySprite.setPosition(sf::Vector2f(200, 200));
        srand(time(0));
    } 

    std::shared_ptr<unit> getRandomSkyUnit(){
            int randomSkyUnit = rand() % 4 + 5;
            std::cout<<"creating sky unit of type: "<< randomSkyUnit<<std::endl;
            std::shared_ptr<unit> newSkyUnit = (factorCard(randomSkyUnit))->summonUnitFromCard();
            newSkyUnit->makeEnemy();
            return newSkyUnit;
    }

    std::shared_ptr<unit> getRandomGroundUnit(){
            int randomGroundUnit = (rand() % 3) ;
            std::cout<<"creating ground unit of type: "<<randomGroundUnit<<std::endl;
            std::shared_ptr<unit> newGroundUnit = (factorCard(randomGroundUnit))->summonUnitFromCard();
            newGroundUnit->makeEnemy();
            return newGroundUnit;
    }

    std::vector<std::shared_ptr<unit>> generateEnemyUnits(int mana = 10){
        int unitGenerationIndex =  rand() % 4;
        
        std::vector<std::shared_ptr<unit>> newEnemyUnits;

        if(unitGenerationIndex == 1){
            newEnemyUnits.push_back(getRandomSkyUnit());
        }else if(unitGenerationIndex == 2){
            newEnemyUnits.push_back(getRandomGroundUnit());
        }else{
            newEnemyUnits.push_back(getRandomSkyUnit());
            newEnemyUnits.push_back(getRandomGroundUnit());
        }
        return newEnemyUnits;
    }

    void draw(sf::RenderWindow& gameWindow){
        gameWindow.draw(combatEnemySprite);
    }



};




#endif