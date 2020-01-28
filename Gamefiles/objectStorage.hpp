#ifndef _OBJECTSTORAGE_HPP_
#define _OBJECTSTORAGE_HPP_

#include "character.hpp"
#include "macrodefinitions.hpp"
//#include "card.hpp"
// #include <iostream>
// #include "memory"
// #include "vector"
// #include "string"
// #include "SFML/Graphics.hpp"
// #include "gameObject.hpp"
// #include "objectStorage.hpp"
// #include "character.hpp"
// #include "fstream"
 #include "operators.hpp"
 #include "testSprite.hpp"
 #include "background.hpp"
 #include <map>
 #include "card.hpp"

class objectStorage {
private:
    std::shared_ptr<gameObject> factorObject(std::ifstream & inputFile);
    void factorNewGameState(std::string stateFileName);
    sf::RenderWindow & window;
    void factorMainCharacter();

public:
    bool swappedActive = false;
    std::string tmpActive;
    std::string keyActive = "Title.txt";
    std::map<std::string, std::shared_ptr<std::vector<std::shared_ptr<gameObject>>>> allVectors;
    std::string returnTarget = "room1.txt";

    std::vector<int> hand;
    std::vector<int> drawPile;
    std::vector<int> discardPile;
    std::vector<int> completeDeck;
    std::vector<std::shared_ptr<card>> cardsInHand;
    deckClass storageDeck;

    //objectStorage();
    objectStorage(sf::RenderWindow & window);
    std::shared_ptr<gameObject> character1;



    
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> & getActive();
    void setActive(std::string newKey);

    void tmpNewActive();
 };

#endif // _OBJECTSTORAGE_HPP_
