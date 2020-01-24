#ifndef _CARD_HPP
#define _CARD_HPP
#include "gameObject.hpp"
#include "exeptions.hpp"
#include "E_lane.hpp"

#include <vector>
#include <fstream>
#include <algorithm>





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
    int cardID;
public:

    card(std::string cardNameString, std::map<std::string, sf::Texture> textureMap, int cardID):
    gameObject(sf::Vector2f(10, 10), sf::Vector2f(1,1),  textureMap, std::string("basicCardFrame"), 5),
    cardID(cardID){
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

    int getCardID(){return cardID;}
    void interact() override {}
    void move(sf::Vector2f moveDirection) override {}
    void update() override {}
    void setFrame(int maxFrame, int textureRow) override {}
    virtual bool checkIfPlayed(sf::Vector2f mousePosition) =0;
    virtual std::shared_ptr<unit> summonUnitFromCard() =0;

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
    summonCard(std::string cardNameString, int cardUnitDamage, int cardUnitHealth, E_lane cardUnitLane, std::map<std::string, sf::Texture> textureMap, int objectID):
        card(cardNameString, textureMap, objectID),
        cardUnitHealth(cardUnitHealth),
        cardUnitDamage(cardUnitDamage),
        cardUnitLane(cardUnitLane)
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


        cardName.setScale(sf::Vector2f(0.2, 0.2));
        objectSprite.setScale(sf::Vector2f(0.2, 0.2));
        summonCardDamage.setScale(sf::Vector2f(0.2, 0.2));
        summonCardHealth.setScale(sf::Vector2f(0.2, 0.2));
        summonCardArtSprite.setScale(sf::Vector2f(0.2, 0.2));        
    }

    



    void draw(sf::RenderWindow& gameWindow){
        summonCardDamage.setFillColor(sf::Color::Red);
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

        cardName.setPosition(sf::Vector2f(objectSprite.getGlobalBounds().left + (0.175 * objectSprite.getGlobalBounds().width) , objectSprite.getGlobalBounds().top + (0.05 * objectSprite.getGlobalBounds().height)));
        summonCardDamage.setPosition(sf::Vector2f(objectSprite.getGlobalBounds().left + (0.26* objectSprite.getGlobalBounds().width) , objectSprite.getGlobalBounds().top + (0.835 * objectSprite.getGlobalBounds().height)));
        summonCardHealth.setPosition(sf::Vector2f(objectSprite.getGlobalBounds().left + (0.68* objectSprite.getGlobalBounds().width) , objectSprite.getGlobalBounds().top + (0.835 * objectSprite.getGlobalBounds().height)));
        summonCardArtSprite.setPosition(objectSprite.getPosition());
        cardName.setPosition(sf::Vector2f(objectSprite.getGlobalBounds().left + (0.175 * objectSprite.getGlobalBounds().width) , objectSprite.getGlobalBounds().top + (0.05 * objectSprite.getGlobalBounds().height)));

    }

    bool checkIfPlayed(sf::Vector2f mousePosition){
        std::cout<<"entered checkIfPlayed" << std::endl;
        return (objectSprite.getGlobalBounds().contains(mousePosition));
    }

    std::shared_ptr<unit> summonUnitFromCard(){
        return std::shared_ptr<unit>(new unit(cardUnitHealth, cardUnitDamage, cardUnitLane, textureMap));
    }
};

class fightHand{
private:
    std::map<int, sf::Vector2f> handPositionMap;
    std::array<std::shared_ptr<card>, 7> cardsInHand;
    std::vector<int> &discardPile;
    sf::Texture handTexture;
    sf::Sprite handSprite;
    int cardCount = 0;
    int lastPlayedCard = 0;
public:

    fightHand(std::vector<int> &discardPile):
    discardPile(discardPile){
        handPositionMap[0] = sf::Vector2f(600, 850);            
        handPositionMap[1] = sf::Vector2f(775, 850);
        handPositionMap[2] = sf::Vector2f(950, 850);
        handPositionMap[3] = sf::Vector2f(1125, 850);
        handPositionMap[4] = sf::Vector2f(1300, 850);
        handPositionMap[5] = sf::Vector2f(1475, 850);
        handPositionMap[6] = sf::Vector2f(1650, 850);

        //std::for_each(cardsInHand.begin(), cardsInHand.end(), [tempMap](auto &i){i.reset(new nullptr);});//( new summonCard(std::string("NULLCARD"), 0, 0, E_lane::groundLane, tempMap, 0)) ;});
        std::for_each(cardsInHand.begin(), cardsInHand.end(), [](auto &i){i = nullptr;});
        handTexture.loadFromFile("gameAssets/cardAssets/handParchment.png");
        handSprite.setTexture(handTexture);
        handSprite.setPosition(sf::Vector2f(400, 750));
        handSprite.setScale(sf::Vector2f(4, 3));
    }

    void drawHand(sf::RenderWindow& gameWindow){
        //std::cout << "entered draw hand function" << std::endl;
        gameWindow.draw(handSprite);
       // std::for_each(cardsInHand.begin(), cardsInHand.end(), [this, &gameWindow](auto &i){if(i != nullptr){std::cout<<"O";}});
        //std::cout<<"|" << std::endl;
        std::for_each(cardsInHand.begin(), cardsInHand.end(), [this, &gameWindow](auto &i){if(i != nullptr){i->draw(gameWindow);}});
        //std::cout<<"drew all cards" << std::endl;
    }

    int amountOfCardsInHand(){
        return cardCount;
    }

    void emptyHand(){
        if(cardCount > 0){
            std::cout<<"entered empty hand function" <<std::endl;
            std::cout<< "current cards in discardPile: " << discardPile.size() << std::endl;
            std::for_each(cardsInHand.begin(), cardsInHand.end(), [this](auto& i){if(i != nullptr){discardPile.push_back(i->getCardID());}});
            std::cout<< "cards in discardPile after emptying: " << discardPile.size() << std::endl;

            //std::for_each(cardsInHand.begin(), cardsInHand.end(), [&tempMap](auto &i){i.reset(nullptr);});//(new summonCard(std::string("NULLCARD"),0, 0, E_lane::groundLane, tempMap, 0)) ;});
            std::for_each(cardsInHand.begin(), cardsInHand.end(), [](auto &i){i = nullptr;});

        }
        cardCount = 0;

    }

    bool addCard(std::shared_ptr<card> newCard){
        std::cout<<"entered add card for card: " << cardCount << std::endl;
        for(int i = 0; i < 7 ; i++){
            if(cardsInHand[i] == nullptr){
                cardsInHand[i] = newCard;
                newCard->setPosition(handPositionMap[i]);
                cardCount++;
                std::cout<<"added objectID: " << newCard->getCardID() << std::endl; 
                return true;
            }
        }
        return false;
    }



    int isCardClicked(sf::Vector2f mousePosition){
       // std::cout<<"entered isCardClicked()" << std::endl;
        if(cardCount > 0){
            for(int i = 0; i < 7 ; i++){
               // std::cout<<"checking card ID's" << std::endl;
                if(cardsInHand[i] != nullptr){
                    if(cardsInHand[i]->getCardID() != 0){
                        std::cout<<"cardID: " << cardsInHand[i]->getCardID() << std::endl;
                        std::cout<<"found card to check for click in pos: " << i << std::endl;
                        std::cout<<cardsInHand[i]->checkIfPlayed(mousePosition) << std::endl;
                        if(cardsInHand[i]->checkIfPlayed(mousePosition)){
                            std::cout<<"found card clicked on: " << i <<std::endl;
                            return i;
                        }
  //                      std::cout<<"not clicked"<<std::endl;
                    }
                }
            }
        }

  //      std::cout<<"no cards clicked" << std::endl;

        return -1;
    }

    std::shared_ptr<unit> playUnitCard(int cardPositionInHand){
        auto unitFromCard = cardsInHand[cardPositionInHand]->summonUnitFromCard();
        discardPile.push_back(cardsInHand[cardPositionInHand]->getCardID());

        //std::map<std::string, sf::Texture> tempMap;
        //auto x = std::make_shared<card>(0, 0, E_lane::groundLane, tempMap, 0);
        //cardsInHand[cardPositionInHand].reset(x.get());
        cardsInHand[cardPositionInHand] = nullptr;
        return unitFromCard;
    }
};



class deckClass{
private:
    std::vector<int> &hand;
    std::vector<int> &drawPile;
    std::vector<int> &discardPile;
    std::vector<int> &completeDeck;
    std::vector<std::shared_ptr<card>> & cardsInHand;
    std::map<int, sf::Vector2f> handPositionMap;
    sf::Font deckStatsFont;
    fightHand cardHand;

    

public:
    sf::Text deckStats_drawPile;
    sf::Text deckStats_discardPile;
    bool fightActive = false;

    deckClass(std::vector<int> &hand, std::vector<int>& drawPile, std::vector<int>&discardPile, std::vector<int>& completeDeck, std::vector<std::shared_ptr<card>> & cardsInHand):
        hand(hand),
        drawPile(drawPile),
        discardPile(discardPile),
        completeDeck(completeDeck),
        cardsInHand(cardsInHand),
        cardHand(discardPile){
            std::vector<int> basisDeck{1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2};
            completeDeck = std::move(basisDeck);
            handPositionMap[0] = sf::Vector2f(600, 850);            
            handPositionMap[1] = sf::Vector2f(775, 850);
            handPositionMap[2] = sf::Vector2f(950, 850);
            handPositionMap[3] = sf::Vector2f(1125, 850);
            handPositionMap[4] = sf::Vector2f(1300, 850);
            handPositionMap[5] = sf::Vector2f(1475, 850);
            handPositionMap[6] = sf::Vector2f(1650, 850);


            deckStatsFont.loadFromFile("gameAssets/cardAssets/cardFont.otf");
            deckStats_drawPile.setFont(deckStatsFont);
            deckStats_drawPile.setString("DrawPile size: " + std::to_string(drawPile.size()));
            deckStats_discardPile.setFont(deckStatsFont);
            deckStats_discardPile.setString("DrawPile size: " + std::to_string(discardPile.size()));
            
            deckStats_drawPile.setPosition(sf::Vector2f(20, 900));
            deckStats_drawPile.setPosition(sf::Vector2f(20, 1000));
            }

    void newFight(){
        std::cout<<"entered newFight" << std::endl;
        cardHand.emptyHand();
        std::cout<<"emptied hand" << std::endl;
       // hand.clear();
        drawPile.clear();
        discardPile.clear();
        drawPile = completeDeck;
        std::random_shuffle(drawPile.begin(), drawPile.end());
        deckStats_discardPile.setString("DrawPile size: " + std::to_string(discardPile.size()));
        deckStats_drawPile.setString("DrawPile size: " + std::to_string(drawPile.size()));

        fightActive = true;
        std::cout<<"start nieuwe fight" << std::endl;
    }

    void DrawHand(sf::RenderWindow& gameWindow){
        if(fightActive){
            cardHand.drawHand(gameWindow);
        }
        deckStats_discardPile.setString("DrawPile size: " + std::to_string(discardPile.size()));
        deckStats_drawPile.setString("DrawPile size: " + std::to_string(drawPile.size()));

        gameWindow.draw(deckStats_drawPile);
        gameWindow.draw(deckStats_discardPile);
    }

    void newHand(){
        std::random_shuffle(drawPile.begin(), drawPile.end());
        cardHand.emptyHand();
        std::cout<<"emptied hand" << std::endl;
        //std::for_each(hand.begin(), hand.end(), [this](auto &i){discardPile.push_back(i);});
        std::cout<<discardPile.size()<<std::endl;
        //hand.clear();

        if(drawPile.size() < 7){
            std::cout<<"drawPile =< 7, size: " << drawPile.size() << std::endl;
            for(int i=0; i< drawPile.size(); i++){
                cardHand.addCard(factorCard(drawPile[i]));
            }
            std::cout<<"hij add de initiele kaarten" << std::endl;
            drawPile.clear();
            drawPile = discardPile;
            discardPile.clear();
            std::random_shuffle(drawPile.begin(), drawPile.end());
            std::cout<<"current drawpile during reset: "<< drawPile.size()  << std::endl;
            std::cout<<"current handsize: " << cardHand.amountOfCardsInHand() << std::endl;


            int cardsInCurrentHand = cardHand.amountOfCardsInHand();
            std::for_each(drawPile.begin(), drawPile.begin() +(7-cardsInCurrentHand), 
                     [this](auto & i){cardHand.addCard(factorCard(i));});
            // for(int i = 0; i < (7- cardHand.amountOfCardsInHand()); i++){
            //     std::cout<<"trying to add card" << std::endl;
            //     int newCardID = drawPile[i];
            //     std::cout<< "newCardID: " << newCardID <<std::endl;
            //     auto newCard = factorCard(newCardID);
            //     std::cout<<"factoredNewCard"<<std::endl;
            //     cardHand.addCard(newCard);
            // }

            std::cout<<"hij add de overige kaarten" << std::endl;
            drawPile.erase(drawPile.begin(), drawPile.begin() + (7-cardsInCurrentHand) );
            std::cout<<"hij reset de hand" << std::endl;
        }else{
            std::for_each(drawPile.begin(), drawPile.begin()+7, [this](auto & i){cardHand.addCard(factorCard(i));});
            //std::for_each(drawPile.begin(), drawPile.begin()+7, [this](auto & i){hc.push_back(i);});
            std::cout<< "added 1 hand" << std::endl;
            drawPile.erase(drawPile.begin(), drawPile.begin()+7);      
        }
        //cardsInHand.clear();
        //std::for_each(hand.begin(), hand.end(), [this](auto & i){cardsInHand.push_back(factorCard(i));});
        // for(int i = 0; i < 7; i++){
        //     cardsInHand[i]->setPosition(handPositionMap[i]);
        // }

        deckStats_discardPile.setString("DrawPile size: " + std::to_string(discardPile.size()));
        deckStats_drawPile.setString("DrawPile size: " + std::to_string(drawPile.size()));

    }


    std::shared_ptr<unit> checkForCardPlay(sf::Vector2i mousePosI){
        sf::Vector2f mousePosF = sf::Vector2f(float(mousePosI.x), float(mousePosI.y));
        std::cout<< "start to check for cards" << std::endl;
        int clickedCardPos = cardHand.isCardClicked(mousePosF);
        std::cout<< "Card clicked at: " << clickedCardPos << std::endl;
        if(clickedCardPos > 0){
            std::cout<<"unit card found" << std::endl;
            auto newUnit = cardHand.playUnitCard(clickedCardPos);
            std::cout<< "unit played" << std::endl;
            return newUnit;
        }else{
            std::cout<<"no cards clicked" << std::endl;
         }

        return nullptr;
    }

    // int checkCardInteraction(sf::Vector2f mousePosition){
    //     return cardHand.isCardClicked(mousePosition);
    // }

    // std::shared_ptr<unit> playUnitCard(int handPosition){
    //     cardHand.
    // }





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
                        return std::shared_ptr<card>(new summonCard(cardName, cardUnitDamage, cardUnitHealth, cardUnitLane, textureMap, objectID)); 
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