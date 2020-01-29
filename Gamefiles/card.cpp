#include "card.hpp"

std::ifstream& operator>>(std::ifstream& input, E_lane& unitLane){
        std::string laneString;
        input>>laneString;
        if(laneString == "groundLane"){
            unitLane = E_lane::groundLane;
            return input;
        }else if(laneString == "skyLane"){
            unitLane = E_lane::skyLane;
            return input;
        }else if(laneString == "traplane"){
            unitLane = E_lane::trapLane;
            return input;
        }else{
            throw invalid_UnitLane(std::string("invalid UnitLane at") + laneString);
        }
}

std::shared_ptr<card> factorCard(int cardID){
        std::ifstream cardFactoryFile("cardFactoryFile.txt");
        int objectID;
        try{
            while(true){
                cardFactoryFile>>objectID;
                if(objectID != 0){
                }
                if(objectID == cardID){
                    std::string cardType;
                    char fileBind;
                    std::string cardName;
                    std::string cardTextureFileName;

                    cardFactoryFile >> cardType >> fileBind;
                    if(!(fileBind == '{')){throw invalid_Factory_Binds("invalid Factory Bind found: " + fileBind);}
                    if(!(cardFactoryFile >> cardName)){throw end_of_file("no cardName found!");}
                    if(!(cardFactoryFile >> cardTextureFileName)){throw end_of_file("invalid textureFilename!");}
                    
                    if(cardType == "summon"){
                        E_lane cardUnitLane;
                        int cardUnitDamage;
                        int cardUnitHealth;
                        int cardManaCost;
                        std::string unitTextureFileName;
                        cardFactoryFile >> cardUnitLane >> cardUnitDamage >> fileBind >> cardUnitHealth >> fileBind >> cardManaCost >> unitTextureFileName;
                        std::map<std::string, sf::Texture> textureMap;

            
                        sf::Texture unitCardFrame;
                        if(cardUnitLane == E_lane::groundLane){
                            unitCardFrame.loadFromFile("gameAssets/cardAssets/summonCardFrame_W.png");
                        }else{
                            unitCardFrame.loadFromFile("gameAssets/cardAssets/summonCardFrame_F.png");
                        }

                        sf::Texture summonCardTexture;
                        summonCardTexture.loadFromFile(cardTextureFileName); 
                        
                        sf::Texture unitTexture;
                        unitTexture.loadFromFile(unitTextureFileName);


                        textureMap["basicCardFrame"] = unitCardFrame;
                        textureMap["cardArtTexture"] = summonCardTexture;
                        textureMap["unitTexture"] = unitTexture;


                        sf::Vector2f textureSheetdimensions;
                        cardFactoryFile >> textureSheetdimensions.x >> fileBind >> textureSheetdimensions.y; 


                        cardFactoryFile >> fileBind;
                        if(!(fileBind == '}')){
                            throw invalid_Factory_Binds("invalid end factory bind");
                        }
                        return std::shared_ptr<card>(new summonCard(cardName, cardUnitDamage, cardUnitHealth, cardManaCost, cardUnitLane, textureMap, objectID, textureSheetdimensions)); 
                    }
                }else{
                    cardFactoryFile.ignore(300, '\n');
                }
            }
        }catch(problem & e){std::cerr<< e.what() <<std::endl;}
        
        return nullptr;

    }

    