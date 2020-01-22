#ifndef _CARD_HPP
#define _CARD_HPP
#include "gameObject.hpp"
#include "memory"
#include "SFML/Graphics.hpp"
#include "exeptions.hpp"
#include "string"
#include <iostream>
#include <vector>
#include <algorithm>

enum E_lane{
  skyLane, groundLane, trapLane  
};


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
                        std::string unitTextureFileName;
                        cardFactoryFile >> cardUnitLane >> cardUnitDamage >> fileBind >> cardUnitHealth >> unitTextureFileName;
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



class unit : public gameObject{
private:
    int unitMaxHealth;
    int unitDamage;
    E_lane unitLane;
    bool ally = true;
public:
    unit(int unitMaxHealth, int unitDamage, E_lane unitLane, std::map<std::string, sf::texture> textureMap):
    gameObject(sf::Vector2f(200, 100), sf::Vector2f(1,1), textureMap, std::string("unitTexture"), 5)
        unitMaxHealth(unitMaxHealth),
        unitDamage(unitDamage),
        unitLane(unitLane){}
    
    ~unit(){}


};




class card : public gameObject{
private:
    sf::Font cardFont;
    sf::Text cardName;
public:

    card(std::string cardName, std::map<std::string, sf::Texture> textureMap):
    gameObject(sf::Vector2f(10, 10), sf::Vector2f(1,1),  textureMap, std::string("basicCardFrame"), 5){
        cardFont.loadFromFile("gameAssets/cardAssets/cardFont.otf");
        cardName.setFont(cardFont);
        cardName.setString(cardName);
        cardName.setOrigin(cardName.getLocalBounds().left +(cardName.getLocalBounds().width / 2),cardName.getLocalBounds().top + (cardName.getLocalBounds().height / 2));
        cardName.setCharacterSize(80);
        cardName.setFillColor(sf::Color::Black);
        cardName.setPosition(sf::Vector2f(objectSprite.getGlobalBounds().left + (0.175 * objectSprite.getGlobalBounds().width) , objectSprite.getGlobalBounds().top + (0.05 * objectSprite.getGlobalBounds().height)));
    }

    virtual draw(sf::RenderWindow& gameWindow) = 0;
    virtual scaleObjects(sf::Vector2f newScale);
    virtual setPosition(sf::Vector2f newPosition);


    void interact(){}
    void move(sf::Vector2f moveDirection){}
    void update(){}
    void setFrame(int maxFrame, int textureRow){}

    virtual std::shared_ptr<unit> summonUnitFromCard() =0;

}



class summonCard : public card{
private:
    int cardUnitHealth;
    int cardUnitDamage;
    sf::Font summonCardFont;
    sf::Text summonCardDamage;
    sf::Text summonCardHealth;
    sf::Sprite summonCardArtSprite;
    E_lane cardUnitLane;

public:
    summonCard(std::string cardName, int cardUnitDamage, int cardUnitHealth, E_lane cardUnitLane, std::map<std::string, sf::Texture> textureMap):
        card(cardName, textureMap),
        cardUnitHealth(cardUnitHealth),
        cardUnitDamage(cardUnitDamage),
        cardUnitLane(cardUnitLane)
    {

        auto cardPosition = objectSprite.getGlobalBounds();

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


        cardName.setScale(sf::Vector2f(0.5, 0.5));
        objectSprite.setScale(sf::Vector2f(0.5, 0.5));
        summonCardDamage.setScale(sf::Vector2f(0.5, 0.5));
        summonCardHealth.setScale(sf::Vector2f(0.5, 0.5));
        summonCardArtSprite.setScale(sf::Vector2f(0.5, 0.5));        

        
    }


    void draw(sf::RenderWindow& gameWindow){
            gameWindow.draw(summonCardArtSprite);
            gameWindow.draw(objectSprite);
            gameWindow.draw(summonCardName);
            gameWindow.draw(summonCardDamage);
            gameWindow.draw(summonCardHealth);
    }

    void scaleObects(sf::Vector2f newScale){
        cardName.setScale(cardName.getScale() * newScale);
        objectSprite.setScale(objectSprite.getScale() * newScale);
        summonCardDamage.setScale(summonCardDamage.getScale() * newScale);
        summonCardHealth.setScale(summonCardHealth.getScale() * newScale);
        summonCardArtSprite.setScale(summonCardSprite.getScale() * newScale);
    }

    void setPosition(sf::Vector2f newPosition){
        objectSprite.setPosition(newPosition);
        auto cardPosition = objectSprite.getGlobalBounds();

        cardName.setPosition(sf::Vector2f(objectSprite.getGlobalBounds().left + (0.175 * objectSprite.getGlobalBounds().width) , objectSprite.getGlobalBounds().top + (0.05 * objectSprite.getGlobalBounds().height)));
        summonCardDamage.setPosition(sf::Vector2f(cardPosition.left + (0.26* cardPosition.width) , cardPosition.top + (0.835 * cardPosition.height)));
        summonCardHealth.setPosition(sf::Vector2f(cardPosition.left + (0.68* cardPosition.width) , cardPosition.top + (0.835 * cardPosition.height)));
        summonCardArtSprite.setPosition(objectSprite.getPosition());
    }

    std::shared_ptr<unit> summonUnitFromCard(){
        return std::shared_ptr<unit>(new unit(cardUnitHealth, cardUnitDamage, cardUnitLane, textureMap));
    }
};

     

class deckClass{
private:
    std::vector<int> &hand;
    std::vector<int> &drawPile;
    std::vector<int> &discardPile;
    std::vector<int> &completeDeck;

public:

    deckClass(std::vector<int> & hand, std::vector<int> &drawPile, std::vector<int> &discardPile, std::vector<int> &completeDeck):
        hand(hand),
        drawPile(drawPile),
        discardPile(discardPile),
        completeDeck(completeDeck){
            int basicDeck[20] = {1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2};
            completeDeck.insert(completeDeck.end(), std::begin(basicDeck), std::end(basicDeck)); 
            delete[] basicDeck;
            }

    void newFight(){
        hand.clear();
        drawPile.clear();
        discardPile.clear();
        drawPile.insert(drawPile.insert, completeDeck.begin(), completeDeck.end());
        std::random_shuffle(drawPile.begin(), drawPile.end());
        newHand();
    }

    void newHand(){
        discardPile.move(discardPile.end(), hand.begin(), hand.end());
        hand.clear();

        if(drawPile.size() < 7){
            hand.move(hand.end(), drawPile.begin(), drawPile.begin()+(drawPile.size()));
            drawPile.move(drawPile.end(), discardPile.begin(), discardPile.end());
            discardPile.clear();
            std::random_shuffle(drawPile.begin(), drawPile.end());
            hand.move(hand.end, drawPile.begin(), (drawPile.begin()+(7 - hand.size())));
        }else{
            hand.move(hand.end(), drawPile.begin(), drawPile.end());
        }
    }

};


#endif