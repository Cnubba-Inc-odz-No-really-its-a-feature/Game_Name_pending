#include "objectStorage.hpp"
#include "button.hpp"
#include "titlecard.hpp"
#include "chest.hpp"
#include "door.hpp"
#include "enemy.hpp"
#include "newGameButton.hpp"

bool fileExists(std::string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> & objectStorage::getActive() {
  if(allVectors[keyActive].get() == nullptr){}
  return allVectors[keyActive];
}

void objectStorage::setActive(std::string newKey, std::string spriteName) {
  if(keyActive.at(0) == 'r') returnTarget = keyActive;
  if(newKey == "room1.txt" && keyActive == "menu.txt") newKey = returnTarget;
  if(newKey == "exit") exit(0);
  if(newKey == "cardgame.txt") {cardHand.newFight(); enemyTex = spriteName;};
  if(newKey != "NONE"){
    std::string checkSaveFile = newKey;
    for( int i = 0; i < 4 ;i++ ){
      checkSaveFile.pop_back();
    }
    checkSaveFile += "Save.txt";
    // if(fileExists(checkSaveFile)){
    //   newKey = checkSaveFile;
    // }
    swappedActive = true;
    tmpActive = newKey;
  }
}

void objectStorage::tmpNewActive(){
  keyActive = tmpActive;
  mapKeys.push_back(tmpActive);
  if(keyActive == "d"){}
  else if (allVectors.count(tmpActive) == 0) {
      allVectors[tmpActive] = std::shared_ptr<std::vector<std::shared_ptr<gameObject>>>(new std::vector<std::shared_ptr<gameObject>>);
      factorNewGameState(tmpActive);
  }
}

void objectStorage::saveObjects(){
  std::ofstream outputFile;
  for( auto mapKey : mapKeys){
    auto vector = allVectors[mapKey].get();
    if( mapKey != "room1Save.txt" && mapKey != "room2Save.txt" && mapKey != "room3Save.txt" && mapKey != "room4Save.txt" && mapKey != "room5Save.txt" && mapKey != "room6Save.txt" && mapKey != "room7Save.txt" && mapKey != "room8Save.txt" ){
      mapKey.pop_back();
      mapKey.pop_back();
      mapKey.pop_back();
      mapKey.pop_back();
      mapKey += "Save.txt";
    }
    if( mapKey != "menuSave.txt" && mapKey != "titleSave.txt" && mapKey != "cardgameSave.txt" && mapKey != "mapSave.txt"){
      outputFile.open(mapKey);
      for(auto & object : *vector){
        if(object.get()->getType() == "TESTSPRITE_E" ){
          outputFile << "objectTypes_E::TESTSPRITE_E ";
        }else if(object.get()->getType() == "CHEST_E"){
          outputFile << "objectTypes_E::CHEST_E ";
        }else if(object.get()->getType() == "DOOR_E"){
          outputFile << "objectTypes_E::DOOR_E ";
        }else if(object.get()->getType() == "ENEMY_E"){
          outputFile << "objectTypes_E::ENEMY_E ";
        }else if(object.get()->getType() == "BACKGROUND_E"){
          outputFile << "objectTypes_E::BACKGROUND_E ";
        }
        sf::Vector2f position = object.get()->getSprite().getPosition();
        outputFile << "(" << position.x << ", " << position.y << ") ";
        sf::Vector2f scale = object.get()->getSprite().getScale();
        outputFile << "(" << scale.x << ", " << scale.y << ") ";
        outputFile << object.get()->objectPriority << " ";
        
        if(object.get()->getType() == "DOOR_E" || object.get()->getType() == "ENEMY_E"){
          outputFile << object.get()->target << " ";
        }
        if(object.get()->getType() == "CHEST_E" || object.get()->getType() == "DOOR_E"){
          outputFile << object.get()->soundFile << " ";
        }
        if(object.get()->getType() == "CHEST_E" || object.get()->getType() == "DOOR_E" || object.get()->getType() == "ENEMY_E"){
          outputFile << object.get()->interacted << " ";
        }
        outputFile << object.get()->firstkey << " ";
        outputFile << object.get()->textureFile << " ";
        outputFile << ";\n";
      }
    }
    outputFile.close();
  }
}


objectStorage::objectStorage(sf::RenderWindow& window) : window(window),
    cardHand(drawPile, discardPile,playerDeck, cardsInHand),
    deckEditor(playerDeck, ownedCards, editorUPButtonArray, editorDOWNButtonArray){
    tmpActive = "title.txt";
    tmpNewActive();
    factorMainCharacter();
    std::cout << "Consturctor objectStorage" << std::endl;
}

std::shared_ptr<gameObject> objectStorage::factorObject(
  std::ifstream& inputFile) {
  objectTypes_E objectType;
  sf::Vector2f pos;
  sf::Vector2f scale;
  std::string idString;
  std::map<std::string, sf::Texture> textureMap;
  std::string textureMapKey;
  std::string textureFile;
  std::string target;
  std::string soundFile;
  sf::Texture objectTexture;
  int textureSheetTiles;

  char textureBind;
  int prio;
  std::string firstKey;
  int interacted;
  try {
    inputFile >> objectType >> pos >> scale >> prio;
    try {
      bool firstrun = true;
      if (objectType == DOOR_E || objectType == BUTTON_E || objectType == ENEMY_E || objectType == NEWGAMEBUTTON_E) {
        inputFile >> target;
      }
      if ( objectType == DOOR_E || objectType == BUTTON_E || objectType == CHEST_E || objectType == NEWGAMEBUTTON_E) {  
        inputFile >> soundFile;
      }
      if ( objectType == DOOR_E || objectType == ENEMY_E || objectType == CHEST_E) {
        inputFile >> interacted;
      }
      if ( objectType == ENEMY_E){
        inputFile >> textureSheetTiles;
      }
      while (true) {
        inputFile >> textureMapKey;
        inputFile >> textureFile;
        objectTexture.loadFromFile(textureFile);
        textureMap[textureMapKey] = objectTexture;
        inputFile >> textureBind;
        if (firstrun) {
          firstKey = textureMapKey;
          firstrun = false;
        }
        if (!(textureBind == ',')) {
          throw end_of_textures("end of textures");
        }
      }
    } catch (end_of_textures& e) {
      std::cerr << e.what() << std::endl;
    }

    if (objectType == objectTypes_E::CHARACTER_E) {
      return std::shared_ptr<gameObject>(
          new character(pos, scale, textureMap, window, firstKey, prio));
    } else if (objectType == objectTypes_E::TESTSPRITE_E) {
      return std::shared_ptr<gameObject>(
          new textureSprite(pos, scale, textureMap, firstKey,prio, textureFile));
    } else if (objectType == objectTypes_E::CHEST_E) {
      return std::shared_ptr<gameObject>(
          new chest(pos, scale, textureMap, firstKey, prio, *this ,soundFile, textureFile, interacted));
    } else if (objectType == objectTypes_E::DOOR_E) {
      return std::shared_ptr<gameObject>(
          new door(pos, scale, textureMap, firstKey, *this, prio, target, soundFile, returnTarget, textureFile, interacted));
    } else if (objectType == objectTypes_E::ENEMY_E) {
      return std::shared_ptr<gameObject>(
          new enemy(pos, scale, textureMap, firstKey, *this, prio, target, textureFile, interacted, textureSheetTiles));
    } else if (objectType == objectTypes_E::BUTTON_E) {
      return std::shared_ptr<gameObject>(
          new button(pos, scale, textureMap, firstKey, *this, prio, target, soundFile, textureFile));
    } else if (objectType == objectTypes_E::BACKGROUND_E) {
      return std::shared_ptr<gameObject>(
          new background(pos, scale, textureMap, firstKey, prio, textureFile));
    } else if (objectType == objectTypes_E::TITLECARD_E) {
      return std::shared_ptr<gameObject>(
          new titlecard(pos, scale, textureMap, *this, firstKey, prio, textureFile));
    } else if (objectType == objectTypes_E::NEWGAMEBUTTON_E) {
      return std::shared_ptr<gameObject>(
          new newGameButton(pos, scale, textureMap, firstKey, *this, prio, target, soundFile, textureFile));
    }

    throw invalid_type("invalid type found");

  } catch (invalid_type& e) {
    std::cerr << e.what() << std::endl;
    throw invalid_type(e.what());
  } catch (unknown_pos& e) {
    std::cerr << e.what() << std::endl;
    throw unknown_pos('p');
  } catch (end_of_file& e) {
    throw end_of_file("end of file reached");
  }
}

void objectStorage::factorNewGameState(std::string stateFileName) {
  std::ifstream inputFile;
  inputFile.open(stateFileName);
  std::cout << stateFileName << std::endl;
  std::string storageType;
  allVectors[stateFileName] = std::shared_ptr<std::vector<std::shared_ptr<gameObject>>>( new std::vector<std::shared_ptr<gameObject>>);
  try {
    while (true) {
      if (inputFile.peek() == EOF) {
        throw end_of_file("end of file reached");
      }
      allVectors[stateFileName]->push_back(factorObject(inputFile));
    }
  } catch (end_of_file& e) {
    std::cerr << e.what() << std::endl;
  } catch (problem& e) {
    std::cerr << e.what() << std::endl;
  }
}

std::string objectStorage::getReturnTarget(){
  return returnTarget;
}

void objectStorage::factorMainCharacter() {
  try {
    std::ifstream characterFile("mainCharacter.txt");
    character1 = factorObject(characterFile);

  } catch (end_of_file& e) {
  } catch (problem& e) {
    std::cerr << e.what() << std::endl;
  }
}


