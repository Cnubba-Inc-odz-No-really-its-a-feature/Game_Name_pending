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
 #include "combatEnemy.hpp"

///\brief
/// the storage class, given by referance to most everything
///\details
/// When setactive is called, the storage automaticlly fills the map vector with all the nesessery object pointer.
class objectStorage {
private:
    std::shared_ptr<gameObject> factorObject(std::ifstream & inputFile);
    sf::RenderWindow & window;
    void factorMainCharacter();
    std::vector<std::string> mapKeys;
public:
    ///\brief
    /// can be called if you want to override a old state with a new instance of the map
    void factorNewGameState(std::string stateFileName);
    bool swappedActive = false;
    std::string enemyTex;
    int enemyTexTextureSheetTiles;
    std::string tmpActive;
    std::string keyActive = "Title.txt";
    std::map<std::string, std::shared_ptr<std::vector<std::shared_ptr<gameObject>>>> allVectors;
    std::string returnTarget = "room1.txt";

   
    std::vector<int> drawPile;
    std::vector<int> discardPile;
    std::array<sf::Sprite, 10> editorUPButtonArray;
    std::array<sf::Sprite, 10> editorDOWNButtonArray;
     std::array<std::shared_ptr<card>, 7> cardsInHand;
    std::map<int, int> ownedCards= {
        {0, 9}, {1, 6}, {2, 5}, {3, 2}, {4, 0},
        {5, 4}, {6, 4}, {7, 4}, {8, 0}, {9, 0}
    };
    std::map<int, int> playerDeck = {
        {0, 7}, {1, 4}, {2, 3}, {3, 2}, {4, 0},
        {5, 2}, {6, 2}, {7, 2}, {8, 0}, {9, 0}
    };
    fightHand cardHand;
    deckEditorClass deckEditor;
    combatEnemy fightEnemy;

    // objectStorage();
    ///\brief
    /// default constructor for the storage, saves the window for some reason
    objectStorage(sf::RenderWindow & window);
    std::shared_ptr<gameObject> character1;

    ///\brief
    /// Saves the game state upon exit, not fully working
    void saveObjects();
    
    ///\brief
    /// Returns a pointer to the active vector with gameobject
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> & getActive();
    void setActive(std::string newKey, std::string spriteName = "");

    ///\brief
    /// nesessery function to enable smooth fade in state switch
    void tmpNewActive();

    ///\brief
    /// returns the return target, needed for the menu to know where in the game we were.
    std::string getReturnTarget();
 };

#endif // _OBJECTSTORAGE_HPP_
