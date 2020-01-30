#ifndef _CARD_HPP
#define _CARD_HPP
#include "gameObject.hpp"
#include "exeptions.hpp"
#include "E_lane.hpp"

#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>





std::ifstream& operator>>(std::ifstream& input, E_lane& unitLane);



class unit : public gameObject{
private:
    int unitMaxHealth;
    int unitCurrentHealth;
    int unitDamage;
    E_lane unitLane;
    bool ally = true;

    int textureFrame = 0;
    int frameCounter = 0;
    sf::Vector2f textureSheetDimensions;
    sf::Vector2f textureFrameBounds;
    sf::Font unitFont;
    sf::Text unitStatsText;

public:
    int mana;

    unit(){}

    unit(int unitMaxHealth, int unitDamage, E_lane unitLane, std::map<std::string, sf::Texture> textureMap, sf::Vector2f textureSheetDimensions, int manaCost):
    gameObject(sf::Vector2f(200, 100), sf::Vector2f(4,4), textureMap, std::string("unitTexture"), 5),
        unitMaxHealth(unitMaxHealth),
        unitCurrentHealth(unitMaxHealth),
        unitDamage(unitDamage),
        unitLane(unitLane),
        textureSheetDimensions(textureSheetDimensions){
            textureFrameBounds = sf::Vector2f(objectSprite.getLocalBounds().width / textureSheetDimensions.x, objectSprite.getLocalBounds().height / textureSheetDimensions.y) ;
       	    objectSprite.setTextureRect(sf::IntRect(textureFrameBounds.x*0, textureFrameBounds.y*0, textureFrameBounds.x, textureFrameBounds.y));
            objectSprite.setOrigin(objectSprite.getLocalBounds().left + (objectSprite.getLocalBounds().width/2), objectSprite.getLocalBounds().top + (objectSprite.getLocalBounds().height));
            
            objectSprite.setScale(-4, 4);

            mana = manaCost;
            std::cout << "mana in unit is: " << mana << std::endl;

            unitFont.loadFromFile("gameAssets/cardAssets/cardFont.otf");
            unitStatsText.setFont(unitFont);

            unitStatsText.setString(std::to_string(unitDamage) + "       " + std::to_string(unitCurrentHealth));
            unitStatsText.setPosition(sf::Vector2f( 
                        objectSprite.getGlobalBounds().left,
                        objectSprite.getGlobalBounds().top + objectSprite.getGlobalBounds().height));

        }
    
    ~unit(){}

    bool isAlly(){
        return ally;
    }

    void makeEnemy(){
        ally = false;
        objectSprite.setScale(4, 4);
    }

    bool checkIsDead(){
        return unitCurrentHealth <= 0;
    }

    int getDamage(){
        return unitDamage;
    }

    void takeDamage(int damage){
        unitCurrentHealth -= damage;
        unitStatsText.setString(std::to_string(unitDamage) + "       " + std::to_string(unitCurrentHealth));
    }

    E_lane getLaneType(){
        return unitLane;
    }
    
    virtual void draw(sf::RenderWindow& gameWindow) override{
        gameWindow.draw(objectSprite);
        gameWindow.draw(unitStatsText);
    }
    void scaleObjects(sf::Vector2f newScale){}
    void setPosition(sf::Vector2f newPosition){
        objectSprite.setPosition(newPosition);
        unitStatsText.setPosition(sf::Vector2f( 
                        objectSprite.getGlobalBounds().left,
                        objectSprite.getGlobalBounds().top + objectSprite.getGlobalBounds().height));

    }

    void interact()override{}
    void move(sf::Vector2f moveDirection)override{}
    void update()override{
        setFrame(3, 0);
    }
    void setFrame(int maxFrame, int textureRow)override{
        if(frameCounter > 10) {frameCounter = 0; textureFrame++;}
	    if(maxFrame < textureFrame) textureFrame = 0;
	    objectSprite.setTextureRect(sf::IntRect(textureFrameBounds.x*textureFrame, textureFrameBounds.y*textureRow, textureFrameBounds.x, textureFrameBounds.y));
	    frameCounter++;
    }
};




class card : public gameObject{
protected:
    sf::Font cardFont;
    sf::Text cardName;
    sf::Text cardManaCost;
    int cardID;
    int mana;
public:

    card(std::string cardNameString, std::map<std::string, sf::Texture> textureMap, int cardID, int manaCost):
    gameObject(sf::Vector2f(10, 10), sf::Vector2f(1,1),  textureMap, std::string("basicCardFrame"), 5),
    cardID(cardID){
        cardFont.loadFromFile("gameAssets/cardAssets/cardFont.otf");
        cardName.setFont(cardFont);
        cardName.setString(cardNameString);
        cardName.setOrigin(cardName.getLocalBounds().left +(cardName.getLocalBounds().width / 2),cardName.getLocalBounds().top + (cardName.getLocalBounds().height / 2));
        cardName.setCharacterSize(80);
        cardName.setFillColor(sf::Color::Black);
        cardName.setPosition(sf::Vector2f(objectSprite.getGlobalBounds().left + (0.175 * objectSprite.getGlobalBounds().width) , objectSprite.getGlobalBounds().top + (0.05 * objectSprite.getGlobalBounds().height)));
   
        cardManaCost.setFont(cardFont);
        cardManaCost.setString(std::to_string(manaCost));
        cardManaCost.setOrigin(cardManaCost.getLocalBounds().left +(cardManaCost.getLocalBounds().width / 2),cardManaCost.getLocalBounds().top + (cardManaCost.getLocalBounds().height / 2));
        cardManaCost.setCharacterSize(160);
        cardManaCost.setFillColor(sf::Color::Black);
        cardManaCost.setPosition(sf::Vector2f(objectSprite.getGlobalBounds().left + (0.85 * objectSprite.getGlobalBounds().width) , objectSprite.getGlobalBounds().top + (0.02 * objectSprite.getGlobalBounds().height)));
        mana = manaCost;
    }

    void draw(sf::RenderWindow& gameWindow){}
    virtual void scaleObjects(sf::Vector2f newScale)=0;
    virtual void setPosition(sf::Vector2f newPosition)=0;

    int getCardID(){return cardID;}

    virtual E_lane getUnitLane() =0;
    void interact() override {}
    void move(sf::Vector2f moveDirection) override {}
    void update() override {}
    void setFrame(int maxFrame, int textureRow) override {}
    virtual bool checkIfPlayed(sf::Vector2f mousePosition) =0;
    virtual std::shared_ptr<unit> summonUnitFromCard() =0;

     int getManaCost(){
        return mana;
    }

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
    sf::Vector2f textureSheetDimensions;

public:
    summonCard(std::string cardNameString, int cardUnitDamage, int cardUnitHealth, int manaCost, E_lane cardUnitLane, std::map<std::string, sf::Texture> textureMap, int objectID, sf::Vector2f textureSheetDimensions):
        card(cardNameString, textureMap, objectID, manaCost),
        cardUnitHealth(cardUnitHealth),
        cardUnitDamage(cardUnitDamage),
        cardUnitLane(cardUnitLane),
        textureSheetDimensions(textureSheetDimensions)
    {

        auto cardPosition = objectSprite.getGlobalBounds();

        summonCardDamage.setFont(cardFont);
        summonCardDamage.setString(std::to_string(cardUnitDamage));
        summonCardDamage.setOrigin(summonCardDamage.getLocalBounds().left + (summonCardDamage.getLocalBounds().width / 2) , summonCardDamage.getLocalBounds().top +(summonCardDamage.getLocalBounds().height / 2));
        summonCardDamage.setCharacterSize(90);
        summonCardDamage.setFillColor(sf::Color::Black);
        summonCardDamage.setPosition(sf::Vector2f(cardPosition.left + (0.26* cardPosition.width) , cardPosition.top + (0.835 * cardPosition.height)));

        summonCardHealth.setFont(cardFont);
        summonCardHealth.setString(std::to_string(cardUnitHealth));
        summonCardHealth.setOrigin(summonCardHealth.getLocalBounds().left +(summonCardHealth.getLocalBounds().width / 2),summonCardHealth.getLocalBounds().top + (summonCardHealth.getLocalBounds().height / 2));
        summonCardHealth.setCharacterSize(90);
        summonCardHealth.setFillColor(sf::Color::Black);
        summonCardHealth.setPosition(sf::Vector2f(cardPosition.left + (0.68* cardPosition.width) , cardPosition.top + (0.835 * cardPosition.height)));

        summonCardArtSprite.setTexture(gameObject::textureMap["cardArtTexture"]);
        summonCardArtSprite.setPosition(objectSprite.getPosition());

        cardName.setScale(sf::Vector2f(0.24, 0.24));
        cardManaCost.setScale(sf::Vector2f(0.24, 0.24));
        objectSprite.setScale(sf::Vector2f(0.24, 0.24));
        summonCardDamage.setScale(sf::Vector2f(0.24, 0.24));
        summonCardHealth.setScale(sf::Vector2f(0.24, 0.24));
        summonCardArtSprite.setScale(sf::Vector2f(0.24, 0.24));        
    }


    void draw(sf::RenderWindow& gameWindow){
            gameWindow.draw(summonCardArtSprite);
            gameWindow.draw(objectSprite);
            gameWindow.draw(cardName);
            gameWindow.draw(summonCardDamage);
            gameWindow.draw(summonCardHealth);
            gameWindow.draw(cardManaCost);
    }

    void scaleObjects(sf::Vector2f newScale) override{

        cardName.setScale(sf::Vector2f(cardName.getScale().x * newScale.x, cardName.getScale().y * newScale.y));
        objectSprite.setScale(sf::Vector2f(objectSprite.getScale().x * newScale.x, objectSprite.getScale().y * newScale.y));
        summonCardDamage.setScale(sf::Vector2f(summonCardDamage.getScale().x * newScale.x, summonCardDamage.getScale().y * newScale.y));
        summonCardHealth.setScale(sf::Vector2f((summonCardHealth.getScale().x * newScale.x) , (summonCardHealth.getScale().y * newScale.y)));
        summonCardArtSprite.setScale(sf::Vector2f((summonCardArtSprite.getScale().x * newScale.x) , (summonCardArtSprite.getScale().y * newScale.y)));
        cardManaCost.setScale(sf::Vector2f((cardManaCost.getScale().x * newScale.x) , (cardManaCost.getScale().y * newScale.y)));

    }

    void setPosition(sf::Vector2f newPosition)override{
        objectSprite.setPosition(newPosition);
        cardName.setPosition(sf::Vector2f(objectSprite.getGlobalBounds().left + (0.175 * objectSprite.getGlobalBounds().width) , objectSprite.getGlobalBounds().top + (0.05 * objectSprite.getGlobalBounds().height)));
        summonCardDamage.setPosition(sf::Vector2f(objectSprite.getGlobalBounds().left + (0.26* objectSprite.getGlobalBounds().width) , objectSprite.getGlobalBounds().top + (0.835 * objectSprite.getGlobalBounds().height)));
        summonCardHealth.setPosition(sf::Vector2f(objectSprite.getGlobalBounds().left + (0.68* objectSprite.getGlobalBounds().width) , objectSprite.getGlobalBounds().top + (0.835 * objectSprite.getGlobalBounds().height)));
        summonCardArtSprite.setPosition(objectSprite.getPosition());
        cardName.setPosition(sf::Vector2f(objectSprite.getGlobalBounds().left + (0.175 * objectSprite.getGlobalBounds().width) , objectSprite.getGlobalBounds().top + (0.05 * objectSprite.getGlobalBounds().height)));
        cardManaCost.setPosition(sf::Vector2f(objectSprite.getGlobalBounds().left + (0.85 * objectSprite.getGlobalBounds().width) , objectSprite.getGlobalBounds().top + (0.02 * objectSprite.getGlobalBounds().height)));

    }

    bool checkIfPlayed(sf::Vector2f mousePosition){
        return (objectSprite.getGlobalBounds().contains(mousePosition));
    }

    std::shared_ptr<unit> summonUnitFromCard(){
        std::cout << "card mana cost gegeven aan unit: " << mana << std::endl;
        return std::shared_ptr<unit>(new unit(cardUnitHealth, cardUnitDamage, cardUnitLane, textureMap, textureSheetDimensions, mana));
    }

    E_lane getUnitLane(){
        return cardUnitLane;
    }

};


std::shared_ptr<card> factorCard(int cardID);



class fightHand{
private:
    std::map<int, sf::Vector2f> handPositionMap;
    std::array<std::shared_ptr<card>, 7> &cardsInHand;
    std::vector<int> &discardPile;
    std::vector<int> &drawPile;
    sf::Font deckStatsFont;
    sf::Text deckStats_drawPile;
    sf::Text deckStats_discardPile;
    sf::Texture handTexture;
    sf::Sprite handSprite;
    int cardCount = 0;
    int lastPlayedCard = 0;
    std::map<int, int> &playerDeck;
public:

    fightHand(std::vector<int> &discardPile, std::vector<int> & drawPile, std::map<int, int> &playerDeck, std::array<std::shared_ptr<card>, 7> &cardsInHand):
    discardPile(discardPile),
    drawPile(drawPile),
    playerDeck(playerDeck),
    cardsInHand(cardsInHand){
        handPositionMap[0] = sf::Vector2f(630, 825);            
        handPositionMap[1] = sf::Vector2f(810, 825);
        handPositionMap[2] = sf::Vector2f(990, 825);
        handPositionMap[3] = sf::Vector2f(1170, 825);
        handPositionMap[4] = sf::Vector2f(1350, 825);
        handPositionMap[5] = sf::Vector2f(1530, 825);
        handPositionMap[6] = sf::Vector2f(1710, 825);

        std::for_each(cardsInHand.begin(), cardsInHand.end(), [](auto &i){i = nullptr;});
        handTexture.loadFromFile("gameAssets/cardAssets/handParchment.png");
        handSprite.setTexture(handTexture);
        handSprite.setPosition(sf::Vector2f(400, 725));
        handSprite.setScale(sf::Vector2f(5, 3));


        deckStatsFont.loadFromFile("gameAssets/cardAssets/cardFont.otf");
        deckStats_drawPile.setFont(deckStatsFont);
        deckStats_drawPile.setString("DrawPile size: " + std::to_string(drawPile.size()));
        deckStats_discardPile.setFont(deckStatsFont);
        deckStats_discardPile.setString("DiscardPile size: " + std::to_string(discardPile.size()));
            
        deckStats_drawPile.setPosition(sf::Vector2f(20, 950));
        deckStats_discardPile.setPosition(sf::Vector2f(20, 1000));
    }

   

    void draw(sf::RenderWindow& gameWindow){
        gameWindow.draw(handSprite);
        std::for_each(cardsInHand.begin(), cardsInHand.end(), [this, &gameWindow](auto &i){if(i != nullptr){i->draw(gameWindow);}});
        deckStats_discardPile.setString("DiscardPile size: " + std::to_string(discardPile.size()));
        deckStats_drawPile.setString("DrawPile size: " + std::to_string(drawPile.size()));
        gameWindow.draw(deckStats_drawPile);
        gameWindow.draw(deckStats_discardPile);
    }

    int currentCardCount(){
        return cardCount;
    }

    void emptyHand(){
        if(cardCount > 0){
            std::for_each(cardsInHand.begin(), cardsInHand.end(), [this](std::shared_ptr<card>& i){if(i != nullptr){discardPile.push_back(i->getCardID());}});
            std::for_each(cardsInHand.begin(), cardsInHand.end(), [](std::shared_ptr<card> &i){i = nullptr;});
        }
        cardCount = 0;
    }

    bool addCard(std::shared_ptr<card> newCard){
        for(int i = 0; i < 7 ; i++){
            if(cardsInHand[i] == nullptr){
                cardsInHand[i] = newCard;
                newCard->setPosition(handPositionMap[i]);
                cardCount++;
                return true;
            }
        }
        return false;
    }


    int isCardClicked(sf::Vector2f mousePosition, int & playerMana, bool skyOpen, bool groundOpen){
        if(cardCount > 0){
            for(int i = 0; i < 7 ; i++){
                if(cardsInHand[i] != nullptr){
                    if(cardsInHand[i]->checkIfPlayed(mousePosition)){
                        if(((cardsInHand[i]->getUnitLane() == E_lane::skyLane && skyOpen) || (cardsInHand[i]->getUnitLane() == E_lane::groundLane && groundOpen)) && (cardsInHand[i]->getManaCost() <= playerMana)){
                            std::cout << "manaCost kaart in isCardClicked: " << cardsInHand[i]->getManaCost() << std::endl;
                            std::cout << "playerMana in isCardClicked: " << playerMana << std::endl;
                            playerMana -= cardsInHand[i]->getManaCost();
                            return i;
                        }
                    }
                }
            }
        }
        return -1;
    }

    std::shared_ptr<unit> playUnitCard(int cardPositionInHand){
        std::shared_ptr<unit> unitFromCard = cardsInHand[cardPositionInHand]->summonUnitFromCard();
        discardPile.push_back(cardsInHand[cardPositionInHand]->getCardID());
        cardsInHand[cardPositionInHand] = nullptr;

        return unitFromCard;
    }


    std::shared_ptr<unit> checkForCardPlay(sf::Vector2i mousePosI, int &playerMana, bool skyOpen = true, bool groundOpen = true){
        sf::Vector2f mousePosF = sf::Vector2f(float(mousePosI.x), float(mousePosI.y));
        int clickedCardPos = isCardClicked(mousePosF, playerMana, skyOpen, groundOpen);
 
        if(clickedCardPos > -1){
            std::shared_ptr<unit> newUnit = playUnitCard(clickedCardPos);
            return newUnit;
        }else{
            return nullptr;
         
        }
    }

    void newHand(){
        std::random_shuffle(drawPile.begin(), drawPile.end());
        emptyHand();
        if(drawPile.size() < 7){
            for(int i=0; i< drawPile.size(); i++){
                addCard(factorCard(drawPile[i]));
            }
            drawPile.clear();
            drawPile = discardPile;
            discardPile.clear();
            std::random_shuffle(drawPile.begin(), drawPile.end());
            int cardsInCurrentHand = currentCardCount();
            std::for_each(drawPile.begin(), drawPile.begin() +(7-cardsInCurrentHand), 
                     [this](auto & i){addCard(factorCard(i));});
            drawPile.erase(drawPile.begin(), drawPile.begin() + (7-cardsInCurrentHand) );

        }else{
            std::for_each(drawPile.begin(), drawPile.begin()+7, [this](auto & i){addCard(factorCard(i));});
            drawPile.erase(drawPile.begin(), drawPile.begin()+7);      
        }
    }


    void newFight(){
        emptyHand();
        drawPile.clear();
        discardPile.clear();

        std::for_each(playerDeck.begin(), playerDeck.end(), [this](auto & i){for(int j = 0; j < i.second; j++){drawPile.push_back(i.first);}});

        std::random_shuffle(drawPile.begin(), drawPile.end());
        newHand();
    }
};

enum class deckState_E {IDLE_E, DECKVIEW_E, FIGHT_E};


class deckEditorClass{
private:
    sf::Texture UPButtonTexture;
    sf::Texture DOWNButtonTexture;
    sf::Texture cardCounterTexture;
    std::map<int, int> & playerDeck;
    std::map<int, int> & ownedCards;

    std::chrono::time_point<std::chrono::system_clock> lastChange;



    std::vector<std::shared_ptr<card>> deckEditorCards;
    std::map<int,sf::Vector2f> cardPositions = {
        {0, sf::Vector2f(200, 100)}, {1, sf::Vector2f(430, 100)}, {2, sf::Vector2f(660, 100)},
        {3, sf::Vector2f(200, 600)}, {4, sf::Vector2f(430, 600)}, {5, sf::Vector2f(1110, 100)},
        {6, sf::Vector2f(1340, 100)},{7, sf::Vector2f(1570, 100)},{8, sf::Vector2f(1110, 600)},
        {9, sf::Vector2f(1340, 600)}
    };

    sf::Font deckFont;
    sf::Text deckStatsText;

    std::array<sf::Sprite, 10> &UPButtonArray;
    std::array<sf::Sprite, 10> &DOWNButtonArray;
    std::array<sf::Sprite, 10> deckCardCounterSpriteArray;
    std::array<sf::Sprite, 10> ownedCardCounterSpriteArray;
    std::array<sf::Text, 10> deckCardCounterTextArray;
    std::array<sf::Text, 10> ownedCardCounterTextArray;
    std::array<sf::Text, 10> owned_deckTextArray;

    int DECK_MAX = 22;


public:
    deckEditorClass(std::map<int, int> &playerDeck, std::map<int, int>& ownedCards, std::array<sf::Sprite, 10> &UPButtonArray, std::array<sf::Sprite, 10> &DOWNButtonArray):
    playerDeck(playerDeck),
    ownedCards(ownedCards),
    UPButtonArray(UPButtonArray),
    DOWNButtonArray(DOWNButtonArray){
        deckFont.loadFromFile("gameAssets/cardAssets/cardFont.otf");
        UPButtonTexture.loadFromFile("gameAssets/cardAssets/upArrow.png");
        DOWNButtonTexture.loadFromFile("gameAssets/cardAssets/downArrow.png");
        cardCounterTexture.loadFromFile("gameAssets/cardAssets/cardCountTexture.png");

        sf::Sprite UPButtonSprite;
        sf::Sprite DOWNButtonSprite;
        sf::Sprite deckCardCounterSprite;
        sf::Sprite ownedCardCounterSprite;

        UPButtonSprite.setTexture(UPButtonTexture);
        DOWNButtonSprite.setTexture(DOWNButtonTexture);
        deckCardCounterSprite.setTexture(cardCounterTexture);
        ownedCardCounterSprite.setTexture(cardCounterTexture);

        UPButtonSprite.setScale(sf::Vector2f(0.03, 0.04));
        DOWNButtonSprite.setScale(sf::Vector2f(0.03, 0.04));
        deckCardCounterSprite.setScale(sf::Vector2f(0.085, 0.075));
        ownedCardCounterSprite.setScale(sf::Vector2f(0.085, 0.075));


        sf::Text deckCardCounterText;
        sf::Text ownedCardCounterText;
        sf::Text owned_deckText;

        deckCardCounterText.setFont(deckFont);
        ownedCardCounterText.setFont(deckFont);
        owned_deckText.setFont(deckFont);

        deckCardCounterText.setFillColor(sf::Color::Black);
        ownedCardCounterText.setFillColor(sf::Color::Black);
        owned_deckText.setFillColor(sf::Color::Black);

        owned_deckText.setString(std::string("Owned            Deck"));
        owned_deckText.setCharacterSize(20);
        deckStatsText.setFont(deckFont);
        deckStatsText.setFillColor(sf::Color::Black);
        deckStatsText.setCharacterSize(60);
        deckStatsText.setString("DeckSize: " + std::to_string(getDeckSize()) + "/ 22");
        deckStatsText.setPosition(sf::Vector2f(700, 525));

        for(int i = 0; i < 10 ; i++ ){


            std::shared_ptr<card> newViewerCard;

            if(i == 4 || i == 8 || i == 9){
                newViewerCard = factorCard(10);
            }else{
                newViewerCard = factorCard(i);
            }
            newViewerCard->scaleObjects(sf::Vector2f(1.2,1.2));
            newViewerCard->setPosition(cardPositions[i]);
            deckEditorCards.push_back(newViewerCard);

            ownedCardCounterSprite.setPosition(sf::Vector2f(cardPositions[i].x, cardPositions[i].y+305));
            DOWNButtonSprite.setPosition(sf::Vector2f(ownedCardCounterSprite.getGlobalBounds().left + ownedCardCounterSprite.getGlobalBounds().width + 5 , cardPositions[i].y+305));
            deckCardCounterSprite.setPosition(sf::Vector2f(DOWNButtonSprite.getGlobalBounds().left + DOWNButtonSprite.getGlobalBounds().width + 5 , cardPositions[i].y+305));
            UPButtonSprite.setPosition(sf::Vector2f(deckCardCounterSprite.getGlobalBounds().left + deckCardCounterSprite.getGlobalBounds().width + 5 , cardPositions[i].y+305));
            ownedCardCounterText.setString(std::to_string(ownedCards[i]));
            ownedCardCounterText.setPosition(sf::Vector2f(ownedCardCounterSprite.getGlobalBounds().left + (ownedCardCounterSprite.getGlobalBounds().width*0.25), cardPositions[i].y+305));
            deckCardCounterText.setString(std::to_string(playerDeck[i]));
            deckCardCounterText.setPosition(sf::Vector2f(deckCardCounterSprite.getGlobalBounds().left + (deckCardCounterSprite.getGlobalBounds().width*0.25), cardPositions[i].y+305));
            owned_deckText.setPosition(sf::Vector2f(ownedCardCounterSprite.getGlobalBounds().left,ownedCardCounterSprite.getGlobalBounds().top + (ownedCardCounterSprite.getGlobalBounds().height)));

            UPButtonArray[i] = UPButtonSprite;
            DOWNButtonArray[i] = DOWNButtonSprite;
            deckCardCounterSpriteArray[i] = deckCardCounterSprite;
            ownedCardCounterSpriteArray[i] = ownedCardCounterSprite;
            deckCardCounterTextArray[i] = deckCardCounterText;
            ownedCardCounterTextArray[i] = ownedCardCounterText;
            owned_deckTextArray[i] = owned_deckText;
        }
    }

    void draw(sf::RenderWindow& gameWindow){
        gameWindow.draw(deckStatsText);
        int count =0;
        for(int i = 0; i<10; i++){
            deckEditorCards[i]->draw(gameWindow);
            gameWindow.draw(UPButtonArray[i]);
            gameWindow.draw(DOWNButtonArray[i]);
            gameWindow.draw(deckCardCounterSpriteArray[i]);
            gameWindow.draw(ownedCardCounterSpriteArray[i]);
            gameWindow.draw(deckCardCounterTextArray[i]);
            gameWindow.draw(ownedCardCounterTextArray[i]);
            gameWindow.draw(owned_deckTextArray[i]);
        }
    }

    int getDeckSize(){
        int count = 0;
        std::for_each(playerDeck.begin(), playerDeck.end(), [&count](auto&i){count += i.second;});
        return count;
    }

    void changeCardCountInDeck(int cardID, int change){
        if(getDeckSize() <= 22 && (playerDeck[cardID] + change) <= ownedCards[cardID] 
        && (playerDeck[cardID] + change) >= 0 
        && std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastChange).count() > 100){
            lastChange = std::chrono::system_clock::now();
            playerDeck[cardID] += change;
            deckCardCounterTextArray[cardID].setString(std::to_string(playerDeck[cardID]));
            deckStatsText.setString("DeckSize: " + std::to_string(getDeckSize()) + " - 22");
        }
    }

    void newOwnCard(int newCard){
        ownedCards[newCard] += 1;
        deckCardCounterTextArray[newCard].setString(std::to_string(playerDeck[newCard]));
        deckStatsText.setString("DeckSize: " + std::to_string(getDeckSize()) + " - 22");

        if(ownedCards[newCard] == 1){
            deckEditorCards[newCard] = factorCard(newCard);
        }
    }
};

#endif