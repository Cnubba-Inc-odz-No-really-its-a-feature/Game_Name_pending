#ifndef _CARD_HPP
#define _CARD_HPP
#include "gameObject.hpp"
#include "memory"
#include "SFML/Graphics.hpp"
#include "exeptions.hpp"
#include "string"
#include <iostream>
#include <vector>

enum E_lane{
  skyLane, groundLane, trapLane  
};

class unit : public gameObject{
private:
    int unitMaxHealth;
    int unitDamage;
    E_lane unitLane;
    bool ally = true;
public:
    unit(int unitMaxHealth, int unitDamage, E_lane unitLane):
        unitMaxHealth(unitMaxHealth),
        unitDamage(unitDamage),
        unitLane(unitLane){}
    
    ~unit(){}


};



class summonCard : public gameObject{
private:
    int cardUnitHealth;
    int cardUnitDamage;
    sf::Font summonCardFont;
    sf::Text summonCardName;
    sf::Text summonCardDamage;
    sf::Text summonCardHealth;

    sf::Sprite summonCardArtSprite;
    E_lane cardUnitLane;

public:
    summonCard(std::string cardName, int cardUnitDamage, int cardUnitHealth, E_lane cardUnitLane, std::map<std::string, sf::Texture> textureMap):
        gameObject(sf::Vector2f(300, 100), sf::Vector2f(1,1),  textureMap, std::string("basicCardFrame"), 1),
        cardUnitHealth(cardUnitHealth),
        cardUnitDamage(cardUnitDamage),
        cardUnitLane(cardUnitLane)
    {

        summonCardName.setScale(sf::Vector2f(0.5, 0.5));
        objectSprite.setScale(sf::Vector2f(0.5, 0.5));
        summonCardDamage.setScale(sf::Vector2f(0.5, 0.5));
        summonCardHealth.setScale(sf::Vector2f(0.5, 0.5));
        summonCardArtSprite.setScale(sf::Vector2f(0.5, 0.5));

        summonCardFont.loadFromFile("gameAssets/cardAssets/cardFont.otf");
        

        auto cardPosition = objectSprite.getGlobalBounds();


        summonCardName.setFont(summonCardFont);
        summonCardName.setString(cardName);
        summonCardName.setOrigin(summonCardName.getLocalBounds().left +(summonCardName.getLocalBounds().width / 2),summonCardName.getLocalBounds().top + (summonCardName.getLocalBounds().height / 2));
        summonCardName.setCharacterSize(80);
        summonCardName.setFillColor(sf::Color::Black);
        summonCardName.setPosition(sf::Vector2f(cardPosition.left + (0.175 * cardPosition.width) , cardPosition.top + (0.05 * cardPosition.height)));


        summonCardDamage.setFont(summonCardFont);
        summonCardDamage.setString(std::to_string(cardUnitDamage));
        summonCardDamage.setOrigin(summonCardDamage.getLocalBounds().left + (summonCardDamage.getLocalBounds().width / 2) , summonCardDamage.getLocalBounds().top +(summonCardDamage.getLocalBounds().height / 2));
        summonCardDamage.setCharacterSize(90);
        summonCardDamage.setFillColor(sf::Color::Black);
        summonCardDamage.setPosition(sf::Vector2f(cardPosition.left + (0.26* cardPosition.width) , cardPosition.top + (0.835 * cardPosition.height)));


        summonCardHealth.setFont(summonCardFont);
        summonCardHealth.setString(std::to_string(cardUnitHealth));
        summonCardHealth.setOrigin(summonCardHealth.getLocalBounds().left +(summonCardHealth.getLocalBounds().width / 2),summonCardHealth.getLocalBounds().top + (summonCardHealth.getLocalBounds().height / 2));
        summonCardHealth.setCharacterSize(90);
        summonCardHealth.setFillColor(sf::Color::Black);
        summonCardHealth.setPosition(sf::Vector2f(cardPosition.left + (0.68* cardPosition.width) , cardPosition.top + (0.835 * cardPosition.height)));


        summonCardArtSprite.setTexture(gameObject::textureMap["cardArtTexture"]);
        summonCardArtSprite.setPosition(objectSprite.getPosition());
        
    }


    void draw(sf::RenderWindow& gameWindow){
            gameWindow.draw(summonCardArtSprite);
            gameWindow.draw(objectSprite);
            gameWindow.draw(summonCardName);
            gameWindow.draw(summonCardDamage);
            gameWindow.draw(summonCardHealth);
    }

     void interact(){}
     void move(sf::Vector2f moveDirection){}
     void update(){}
     void setFrame(int maxFrame, int textureRow){}


};


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
            throw invalid_UnitLane("invalid UnitLane");
        }
    }
    



class deckClass{
private:
    std::vector<int> completeDeck;
    std::vector<int> drawPile;
    std::vector<int> discardPile;
    std::vector<int> hand;

public:

    std::vector<std::shared_ptr<gameObject>> drawNewHand(){
        

    }





    std::shared_ptr<gameObject> factorCard(int cardID){
        std::ifstream cardFactoryFile("cardFactoryFile.txt");
        int objectID;
        try{
            while(true){
                cardFactoryFile>>objectID;
                if(objectID != 0){
                    std::cout<<objectID << std::endl;
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
                        std::string cardUnitTextureFileName;
                        cardFactoryFile >> cardUnitLane >> cardUnitDamage >> fileBind >> cardUnitHealth >> cardUnitTextureFileName;
                        std::map<std::string, sf::Texture> textureMap;

            
                        sf::Texture unitCardFrame;


                        if(cardUnitLane == E_lane::groundLane){
                            unitCardFrame.loadFromFile("gameAssets/cardAssets/summonCardFrame_W.png");
                        }else{
                            unitCardFrame.loadFromFile("gameAssets/cardAssets/summonCardFrame_F.png");
                        }

                        sf::Texture summonCardTexture;
                        summonCardTexture.loadFromFile(cardTextureFileName); 
                        
                        sf::Texture cardUnitTexture;
                        cardUnitTexture.loadFromFile(cardUnitTextureFileName);
                       // sf::Texture unitTexture;




                        textureMap["basicCardFrame"] = unitCardFrame;
                        textureMap["cardArtTexture"] = summonCardTexture;
                        //textureMap["unitTexture"] = unitTexture;

                        cardFactoryFile >> fileBind;
                        if(!(fileBind == '}')){throw invalid_Factory_Binds("invalid end factory bind");}


                        return std::shared_ptr<gameObject> (new summonCard(cardName, cardUnitDamage, cardUnitHealth, cardUnitLane, textureMap)); 
                    }
                }else{
                    cardFactoryFile.ignore(300, '\n');
                }
            }
        }catch(problem & e){std::cerr<< e.what() <<std::endl;}
        return nullptr;

    }




    // std::shared_ptr<gameObject> factorCard(int cardID){
    //     std::ifstream cardFactoryFile("cardFactoryFile.txt");
    //     int objectID;
    //     try{
    //         while(true){
    //             cardFactoryFile>>objectID;
    //             std::cout<<objectID << std::endl;
    //             if(objectID == cardID){
    //                 std::string cardType;
    //                 char fileBind;
    //                 std::string cardName;
    //                 std::string cardTextureFileName;

    //                 cardFactoryFile >> cardType >> fileBind;
    //                 if(!(fileBind == '{')){throw invalid_Factory_Binds("invalid Factory Bind found: " + fileBind);}
    //                 if(!(cardFactoryFile >> cardName)){throw end_of_file("no cardName found!");}
    //                 if(!(cardFactoryFile >> cardTextureFileName)){throw end_of_file("invalid textureFilename!");}
                    
    //                 if(cardType == "summon"){
    //                     E_lane cardUnitLane;
    //                     int cardUnitDamage;
    //                     int cardUnitHealth;
    //                     std::string cardUnitTextureFileName;
    //                     cardFactoryFile >> cardUnitLane >> cardUnitDamage >> fileBind >> cardUnitHealth >> cardUnitTextureFileName;
    //                     std::map<std::string, sf::Texture> textureMap;

            
    //                     sf::Texture unitCardFrame;


    //                     if(cardUnitLane == E_lane::groundLane){
    //                         unitCardFrame.loadFromFile("gameAssets/cardAssets/summonCardFrame_W.png");
    //                     }else{
    //                         unitCardFrame.loadFromFile("gameAssets/cardAssets/summonCardFrame_F.png");
    //                     }

    //                     sf::Texture summonCardTexture;
    //                     summonCardTexture.loadFromFile(cardTextureFileName); 
                        
    //                     sf::Texture cardUnitTexture;
    //                     cardUnitTexture.loadFromFile(cardUnitTextureFileName);
    //                    // sf::Texture unitTexture;




    //                     textureMap["basicCardFrame"] = unitCardFrame;
    //                     textureMap["cardArtTexture"] = summonCardTexture;
    //                     //textureMap["unitTexture"] = unitTexture;

    //                     cardFactoryFile >> fileBind;
    //                     if(!(fileBind == '}')){throw invalid_Factory_Binds("invalid end factory bind");}


    //                     return std::shared_ptr<gameObject> (new summonCard(cardName, cardUnitDamage, cardUnitHealth, cardUnitLane, textureMap)); 
    //                 }
    //             }else{
    //                     std::cout<<"card ignored" <<std::endl;
    //                 cardFactoryFile.ignore(1, '\n');
    //             }
    //         }
    //     }catch(problem & e){std::cerr<< e.what() <<std::endl;}
    //     return nullptr;

    // }
};


#endif