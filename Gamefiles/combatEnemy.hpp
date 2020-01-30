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
    combatEnemy(std::string textureFileName){
        combatEnemyTexture.loadFromFile(textureFileName);
        combatEnemySprite.setTexture(combatEnemyTexture);
        combatEnemySprite.setPosition(sf::Vector2f(800, 500));
        srand(time(0));
    } 

    std::shared_ptr<unit> getRandomSkyUnit(){
            int randomSkyUnit = rand() % 4 + 5;
            std::shared_ptr<unit> newSkyUnit = (factorCard(randomSkyUnit))->summonUnitFromCard();
            newSkyUnit->makeEnemy();
            return newSkyUnit;
    }

    std::shared_ptr<unit> getRandomGroundUnit(){
            int randomGroundUnit = (rand() % 3) ;
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

    void getNewSprite(std::string newTextureFileName, int textureSheetTiles){
        combatEnemyTexture.loadFromFile(newTextureFileName);
        combatEnemySprite.setTexture(combatEnemyTexture);
        combatTextureSheetTiles = textureSheetTiles;
        textureFrameBounds = sf::Vector2f(combatEnemySprite.getLocalBounds().width / textureSheetTiles, combatEnemySprite.getLocalBounds().height) ;
        combatEnemySprite.setPosition(sf::Vector2f(800, 100));
    }

    void setFrame(int maxFrame, int textureRow){
        if(frameCounter > 10) {frameCounter = 0; textureFrame++;}
	    if(maxFrame < textureFrame) textureFrame = 0;
	    combatEnemySprite.setTextureRect(sf::IntRect((textureFrameBounds.x*textureFrame)+47, (textureFrameBounds.y*textureRow)-10, textureFrameBounds.x - 97, textureFrameBounds.y));
	    combatEnemySprite.setOrigin(sf::Vector2f(combatEnemySprite.getLocalBounds().width/2, 0));
        frameCounter++;
    }

    void draw(sf::RenderWindow& gameWindow){
        setFrame(combatTextureSheetTiles-1, 0);
        gameWindow.draw(combatEnemySprite);
    }



};




#endif