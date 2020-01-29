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
    std::vector<std::string> mapKeys;
public:
    bool swappedActive = false;
    std::string tmpActive;
    std::string keyActive = "Title.txt";
    std::map<std::string, std::shared_ptr<std::vector<std::shared_ptr<gameObject>>>> allVectors;
    std::string returnTarget = "room1.txt";

   
    std::vector<int> drawPile;
    std::vector<int> discardPile;
    std::array<sf::Sprite, 10> editorUPButtonArray;
    std::array<sf::Sprite, 10> editorDOWNButtonArray;
    std::vector<std::shared_ptr<card>> cardsInHand;
    std::map<int, int> ownedCards= {
        {0, 7}, {1, 4}, {2, 3}, {3, 2}, {4, 0},
        {5, 2}, {6, 2}, {7, 2}, {8, 0}, {9, 0}
    };;
    std::map<int, int> playerDeck = ownedCards;
    fightHand cardHand;
    deckEditorClass deckEditor;

    //objectStorage();
    objectStorage(sf::RenderWindow & window);
    std::shared_ptr<gameObject> character1;

    void saveObjects();
    
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> & getActive();
    void setActive(std::string newKey);

    void tmpNewActive();
    std::string getReturnTarget();
 };

#endif // _OBJECTSTORAGE_HPP_
