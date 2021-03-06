#ifndef _COMBATENEMY_HPP
#define _COMBATENEMY_HPP
#include "card.hpp"

/// \brief
/// Enemy AI
/// \details
/// A very dumb and unfair AI, since it just plays random cards without mana constraint
class combatEnemy{
private:
    sf::Texture combatEnemyTexture;
    sf::Sprite combatEnemySprite;
    int textureFrame = 0;
    int frameCounter = 0;
    int combatTextureSheetTiles = 0;
    sf::Vector2f textureFrameBounds;

public:
    /// \brief
    /// Constructor, inits the random generator
    combatEnemy(){
        srand(time(0));
    } 

    /// \brief
    /// Returns a randomly choosen sky unit
    std::shared_ptr<unit> getRandomSkyUnit(){
            int randomSkyUnit = rand() % 5 + 5;
            std::shared_ptr<unit> newSkyUnit = (factorCard(randomSkyUnit))->summonUnitFromCard();
            newSkyUnit->makeEnemy();
            return newSkyUnit;
    }

    /// \brief
    /// Returns a randomly choosen ground unit
    std::shared_ptr<unit> getRandomGroundUnit(){
            int randomGroundUnit = (rand() % 4) ;
            std::shared_ptr<unit> newGroundUnit = (factorCard(randomGroundUnit))->summonUnitFromCard();
            newGroundUnit->makeEnemy();
            return newGroundUnit;
    }

    /// \brief
    /// returns one or two units to play on the board
    std::vector<std::shared_ptr<unit>> generateEnemyUnits(bool skyOpen, bool groundOpen, int mana = 10){
        int unitGenerationIndex =  rand() % 4;
        
        std::vector<std::shared_ptr<unit>> newEnemyUnits;

        if(skyOpen && unitGenerationIndex == 2 ||unitGenerationIndex == 3 || unitGenerationIndex == 0){
            newEnemyUnits.push_back(getRandomSkyUnit());
        }
        if(groundOpen && unitGenerationIndex == 1 || unitGenerationIndex == 4 || unitGenerationIndex == 3){
            newEnemyUnits.push_back(getRandomGroundUnit());
        }
        return newEnemyUnits;
    }

    /// \brief
    /// Gets called at the start of the fight, so the texture is the same as the enemy found in the dungeon
    void setNewEnemy(std::string newTextureFileName, int &textureSheetTiles){
        combatEnemySprite.setPosition(sf::Vector2f(1750, 420));
        combatEnemySprite.setScale(-4, 4);  
        combatEnemyTexture.loadFromFile(newTextureFileName);
        combatEnemySprite.setTexture(combatEnemyTexture);
        combatTextureSheetTiles = 0;
        combatTextureSheetTiles = textureSheetTiles;
        textureFrameBounds = sf::Vector2f(combatEnemySprite.getLocalBounds().width / textureSheetTiles, combatEnemySprite.getLocalBounds().height) ;
    }

    /// \brief
    /// Implemented for the anamation
    void setFrame(int maxFrame, int textureRow){
        if(frameCounter > 5) {frameCounter = 0; textureFrame++;}
	    if(maxFrame < textureFrame) textureFrame = 0;
	    combatEnemySprite.setTextureRect(sf::IntRect((textureFrameBounds.x*textureFrame), (textureFrameBounds.y*textureRow), textureFrameBounds.x , textureFrameBounds.y));
	    combatEnemySprite.setOrigin(sf::Vector2f(combatEnemySprite.getLocalBounds().width/2, 0));
        frameCounter++;
    }

    /// \brief
    /// Draws the enemy unit
    void draw(sf::RenderWindow& gameWindow){
        setFrame(combatTextureSheetTiles-1, 0);
        gameWindow.draw(combatEnemySprite);
    }



};




#endif