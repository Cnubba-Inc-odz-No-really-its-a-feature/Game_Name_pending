#ifndef _CARD_HPP
#define _CARD_HPP
#include "gameObject"
#include "memory"
#include "SFML/Graphics.hpp"
#include "exception.hpp"

enum E_lane{
  skyLane, groundLane, trapLane  
};

class unit : public gameObject{
private:
    int unitMaxHealth;
    int unitDamage;
    E_lane unitLane;
public:
    unit(int unitMaxHealth, int unitDamage, E_lane unitLane):
        unitMaxHealth(unitMaxHealth),
        unitDamage(unitDamage),
        unitLane(unitLane){}
    
    ~unit(){}


};

class card : public GameObject{
private:
    int cardName;
    sf::Sprite cardArtSprite;
    sf::Sprite basicCardFrameSprite;
public:
    card(std::string cardName, std::map<std::string, sf::Texture> textureMap):
    gameObject(sf::Vector2f(0,0), sf::Vector2f(1,1), textureMap, 1),
    cardName(cardName){
        cardArtSprite.setTexture(textureMap["cardArtTexture"]);
        basicCardFrameSprite.setTexture(textureMap["basicCardFrame"]);
    }


    void draw(sf::RenderWindow & gameWindow){
        gameWindow.draw(cardArtSprite);
        gameWindow.draw(basicCardFrameSprite);
    }



};


class summonCard : public card{
private:
    int cardUnitHealth;
    int cardUnitDamage;
    E_lane cardUnitLane;

    summonCard(std::string cardName, int cardUnitDamage, int cardUnitHealth, E_lane cardUnitLane, std::map<std::string, sf::Texture> textureMap):
    card(cardName, textureMap),
    cardUnitHealth(cardUnitHealth),
    cardUnitDamage(cardUnitDamage),
    cardUnitLane(cardUnitLane)
    {}

}


class deckClass{
public:


    std::ifstream& operator>>(std::ifstream& input, E_Lane& unitLane){
        std::string laneString;
        input>>laneString;
        if(laneString == "groundLane"){
            unitLane = E_lane::groundlane;
            return input;
        }else if(laneString == "skylane"){
            unitLane = E_lane::skylane;
            return input;
        }else if(laneString == "traplane"){
            unitLane = E_lane::traplane;
            return input;
        }else{
            throw invalid_UnitLand("invalid UnitLane");
        }
    }


    std::shared_ptr<gameObject> factorCard(int cardID){
        std::ifstream cardFactoryFile("cardFactoryFile.txt");
        int objectID;
        try{
            while(true){
                cardFactoryFile>>objectID;
                if(objectID == cardID){
                    std::string cardType;
                    char fileBind;
                    std::string cardName;
                    std::string cardTextureFileName;

                    cardFactoryFile >> cardType >> fileBind;
                    if(!(fileBind == '{')){throw invalid_Factory_Binds("invalid Factory Bind found: " + fileBind);}
                    if(!(cardFactoryFile >> cardName){throw end_Of_File("no cardName found!");}
                    if(!(cardFactoryFile >> cardTextureFileName)){throw end_Of_File("invalid textureFilename!");}

                    if(cardType == "summon"){
                        E_Lane cardUnitLane;
                        int cardUnitDamage;
                        int cardunitHealth;
                        std::string cardUnitTextureFileName;
                        cardFactoryFile >> cardUnitLane >> cardUnitDamage >> fileBind >> cardUnitHealth >> cardUnitTextureFileName;
                        std::map<std::string, sf::Texture> textureMap;

            
                        sf::Texture unitCardFrame;
                        basicCardFrame.loadFromFile("cardFrame.png");
                        sf::Texture cardUnitTexture;
                        sf::Texture unitTexture;

                        textureMap["basicCardFrame"] = unitCardFrame;
                        textureMap["cardArtTexture"] = cardUnitTexture;
                        textureMap["unitTexture"] = unitTexture;

                        cardFactoryFile >> fileBind;
                        if(!(fileBind == '}')){throw invalid_Factory_Binds("invalid end factory bind");}


                        return std::shared_ptr<gameObject> (new summonCard(cardName, cardUnitDamage, cardUnitHealth, cardUnitLane, textureMap)); 
                    }
                }else{
                    cardFactoryFile.ignore();
                }
            }
        }catch(problem & e){std::cerr<< e.what() <<std::endl;}

    }
}


#endif