#ifndef _COMBATENEMY_HPP
#define _COMBATENEMY_HPP
#include "card.hpp"

class combatEnemy{
private:
    sf::Texture combatEnemyTexture;
    sf::Sprite combatEnemySprite;
    int textureFrame = 0;
    int frameCounter = 0;
    int combatTextureSheetTiles = 0;
    sf::Vector2f textureFrameBounds;

public:
    combatEnemy(){
        srand(time(0));
    } 

    std::shared_ptr<unit> getRandomSkyUnit(){
            int randomSkyUnit = rand() % 5 + 5;
            std::shared_ptr<unit> newSkyUnit = (factorCard(randomSkyUnit))->summonUnitFromCard();
            newSkyUnit->makeEnemy();
            return newSkyUnit;
    }

    std::shared_ptr<unit> getRandomGroundUnit(){
            int randomGroundUnit = (rand() % 4) ;
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

    void setNewEnemy(std::string newTextureFileName, int &textureSheetTiles){
        combatEnemySprite.setPosition(sf::Vector2f(1750, 420));
        combatEnemySprite.setScale(-4, 4);  
        combatEnemyTexture.loadFromFile(newTextureFileName);
        combatEnemySprite.setTexture(combatEnemyTexture);
        combatTextureSheetTiles = 0;
        combatTextureSheetTiles = textureSheetTiles;
        textureFrameBounds = sf::Vector2f(combatEnemySprite.getLocalBounds().width / textureSheetTiles, combatEnemySprite.getLocalBounds().height) ;
    }

    void setFrame(int maxFrame, int textureRow){
        if(frameCounter > 5) {frameCounter = 0; textureFrame++;}
	    if(maxFrame < textureFrame) textureFrame = 0;
	    combatEnemySprite.setTextureRect(sf::IntRect((textureFrameBounds.x*textureFrame), (textureFrameBounds.y*textureRow), textureFrameBounds.x , textureFrameBounds.y));
	    combatEnemySprite.setOrigin(sf::Vector2f(combatEnemySprite.getLocalBounds().width/2, 0));
        frameCounter++;
    }

    void draw(sf::RenderWindow& gameWindow){
        setFrame(combatTextureSheetTiles-1, 0);
        gameWindow.draw(combatEnemySprite);
    }



};




#endif