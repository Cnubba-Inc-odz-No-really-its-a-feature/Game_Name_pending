#ifndef _CARD_HPP
#define _CARD_HPP
#include "gameObject.hpp"
#include "exeptions.hpp"
#include <vector>

#include <fstream>
#include <algorithm>

enum E_lane{
  skyLane, groundLane, trapLane  
};



std::ifstream& operator>>(std::ifstream& input, E_lane& unitLane);




class unit : public gameObject{
private:
    int unitMaxHealth;
    int unitCurrentHealth;
    int unitDamage;
    E_lane unitLane;
    bool ally = true;
public:
    unit(int unitMaxHealth, int unitDamage, E_lane unitLane, std::map<std::string, sf::Texture> textureMap):
    gameObject(sf::Vector2f(200, 100), sf::Vector2f(1,1), textureMap, std::string("unitTexture"), 5),
        unitMaxHealth(unitMaxHealth),
        unitCurrentHealth(unitMaxHealth),
        unitDamage(unitDamage),
        unitLane(unitLane){}
    
    ~unit(){}

    bool isAlly(){
        return ally;
    }

    bool checkIsDead(){
        return unitCurrentHealth <= 0;
    }

    int getDamage(){
        return unitDamage;
    }

    void takeDamage(int damage){
        unitCurrentHealth -= damage;
    }

    E_lane getLaneType(){
        return unitLane;
    }
    
    void draw(sf::RenderWindow& gameWindow) override{
        gameWindow.draw(objectSprite);
    }
    void scaleObjects(sf::Vector2f newScale){}
    void setPosition(sf::Vector2f newPosition){}

    void interact()override{}
    void move(sf::Vector2f moveDirection)override{}
    void update()override{}
    void setFrame(int maxFrame, int textureRow)override{}



};




class card : public gameObject{
protected:
    sf::Font cardFont;
    sf::Text cardName;
public:

    card(std::string cardNameString, std::map<std::string, sf::Texture> textureMap):
    gameObject(sf::Vector2f(10, 10), sf::Vector2f(1,1),  textureMap, std::string("basicCardFrame"), 5){
        cardFont.loadFromFile("gameAssets/cardAssets/cardFont.otf");
        cardName.setFont(cardFont);
        cardName.setString(cardNameString);
        cardName.setOrigin(cardName.getLocalBounds().left +(cardName.getLocalBounds().width / 2),cardName.getLocalBounds().top + (cardName.getLocalBounds().height / 2));
        cardName.setCharacterSize(80);
        cardName.setFillColor(sf::Color::Black);
        cardName.setPosition(sf::Vector2f(objectSprite.getGlobalBounds().left + (0.175 * objectSprite.getGlobalBounds().width) , objectSprite.getGlobalBounds().top + (0.05 * objectSprite.getGlobalBounds().height)));
    }

    void draw(sf::RenderWindow& gameWindow){}
    virtual void scaleObjects(sf::Vector2f newScale)=0;
    virtual void setPosition(sf::Vector2f newPosition)=0;


    void interact() override {}
    void move(sf::Vector2f moveDirection) override {}
    void update() override {}
    void setFrame(int maxFrame, int textureRow) override {}

    virtual std::shared_ptr<gameObject> summonUnitFromCard() =0;

};



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
    summonCard(std::string cardNameString, int cardUnitDamage, int cardUnitHealth, E_lane cardUnitLane, std::map<std::string, sf::Texture> textureMap):
        card(cardNameString, textureMap),
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
            gameWindow.draw(cardName);
            gameWindow.draw(summonCardDamage);
            gameWindow.draw(summonCardHealth);
    }

    void scaleObjects(sf::Vector2f newScale) override{

        cardName.setScale(sf::Vector2f(cardName.getScale().x * newScale.x, cardName.getScale().y * newScale.y));
        objectSprite.setScale(sf::Vector2f(objectSprite.getScale().x * newScale.x, objectSprite.getScale().y * newScale.y));
        summonCardDamage.setScale(sf::Vector2f(summonCardDamage.getScale().x * newScale.x, summonCardDamage.getScale().y * newScale.y));
        summonCardHealth.setScale(sf::Vector2f((summonCardHealth.getScale().x * newScale.x) , (summonCardHealth.getScale().y * newScale.y)));
        summonCardArtSprite.setScale(sf::Vector2f((summonCardArtSprite.getScale().x * newScale.x) , (summonCardArtSprite.getScale().y * newScale.y)));
    }

    void setPosition(sf::Vector2f newPosition)override{
        objectSprite.setPosition(newPosition);
        auto cardPosition = objectSprite.getGlobalBounds();

        cardName.setPosition(sf::Vector2f(objectSprite.getGlobalBounds().left + (0.175 * objectSprite.getGlobalBounds().width) , objectSprite.getGlobalBounds().top + (0.05 * objectSprite.getGlobalBounds().height)));
        summonCardDamage.setPosition(sf::Vector2f(cardPosition.left + (0.26* cardPosition.width) , cardPosition.top + (0.835 * cardPosition.height)));
        summonCardHealth.setPosition(sf::Vector2f(cardPosition.left + (0.68* cardPosition.width) , cardPosition.top + (0.835 * cardPosition.height)));
        summonCardArtSprite.setPosition(objectSprite.getPosition());
    }

    std::shared_ptr<gameObject> summonUnitFromCard(){
        return std::shared_ptr<gameObject>(new unit(cardUnitHealth, cardUnitDamage, cardUnitLane, textureMap));
    }
};

     

class deckClass{
private:
    std::vector<int> &hand;
    std::vector<int> &drawPile;
    std::vector<int> &discardPile;
    std::vector<int> &completeDeck;

public:

    deckClass(std::vector<int> &hand, std::vector<int>& drawPile, std::vector<int>&discardPile, std::vector<int>& completeDeck):
        hand(hand),
        drawPile(drawPile),
        discardPile(discardPile),
        completeDeck(completeDeck){
            std::vector<int> basisDeck{1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2};

            completeDeck.push_back(1);
            std::move(basisDeck.begin(), basisDeck.end(), completeDeck.end());

            }

    void newFight(){
        hand.clear();
        drawPile.clear();
        discardPile.clear();
        drawPile.insert(drawPile.end(), completeDeck.begin(), completeDeck.end());
        std::random_shuffle(drawPile.begin(), drawPile.end());
        newHand();
    }

    void newHand(){

        std::move(hand.begin(), hand.end(), discardPile.end());
        hand.clear();
        if(drawPile.size() < 7){
            std::move(drawPile.begin(), drawPile.begin()+drawPile.size(), hand.end());
            std::move(discardPile.begin(), discardPile.end(), drawPile.end());
            discardPile.clear();
            std::random_shuffle(drawPile.begin(), drawPile.end());
            std::move(drawPile.begin(), drawPile.begin() + (7 - hand.size()), hand.end());
        }else{
            std::move(drawPile.begin(), drawPile.begin()+7, hand.end());
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
                        if(!(fileBind == '}')){
                            throw invalid_Factory_Binds("invalid end factory bind");
                        }
                        return std::shared_ptr<card>(new summonCard(cardName, cardUnitDamage, cardUnitHealth, cardUnitLane, textureMap)); 
                    }
                }else{
                    cardFactoryFile.ignore(300, '\n');
                }
            }
        }catch(problem & e){std::cerr<< e.what() <<std::endl;}
        
        
        return nullptr;

    }

};


#endif