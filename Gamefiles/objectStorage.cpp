#include "objectStorage.hpp"
#include "button.hpp"
#include "titlecard.hpp"
#include "chest.hpp"
#include "door.hpp"

std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> & objectStorage::getActive() {
  if(allVectors[keyActive].get() == nullptr){}
  return allVectors[keyActive];
}

void objectStorage::setActive(std::string newKey) {
  swappedActive = true;
  tmpActive = newKey;
}

void objectStorage::tmpNewActive(){
  keyActive = tmpActive;
  allVectors.clear();
  if (allVectors.count(tmpActive) == 0) {
    std::cout << "Test11" << std::endl;
      allVectors[tmpActive] = std::shared_ptr<std::vector<std::shared_ptr<gameObject>>>(new std::vector<std::shared_ptr<gameObject>>);
      std::cout << "Test12" << std::endl;
      factorNewGameState(tmpActive);
      std::cout << "Test13" << std::endl;
  }
}

objectStorage::objectStorage(sf::RenderWindow& window) : window(window),
    storageDeck(hand, drawPile, discardPile, completeDeck){
    tmpActive = "title.txt";
    tmpNewActive();
    factorMainCharacter();
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
  sf::Texture objectTexture;
  char textureBind;
  int prio;
  std::string firstKey;

  try {
    inputFile >> objectType >> pos >> scale >> prio;
    try {
      bool firstrun = true;
      if (objectType == DOOR_E || objectType == BUTTON_E) {
        inputFile >> target;
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
          throw end_of_textures("end of textures reached");
        }
      }
    } catch (end_of_textures& e) {
      std::cerr << e.what() << std::endl;
    };

    if (objectType == objectTypes_E::CHARACTER_E) {
      return std::shared_ptr<gameObject>(
          new character(pos, scale, textureMap, window, firstKey, prio));
    } else if (objectType == objectTypes_E::TESTSPRITE_E) {
      return std::shared_ptr<gameObject>(
          new textureSprite(pos, scale, textureMap, firstKey, prio));
    } else if (objectType == objectTypes_E::CHEST_E) {
      return std::shared_ptr<gameObject>(
          new chest(pos, scale, textureMap, firstKey, prio));
    } else if (objectType == objectTypes_E::DOOR_E) {
      return std::shared_ptr<gameObject>(
          new door(pos, scale, textureMap, firstKey, *this, prio, target));
    } else if (objectType == objectTypes_E::BUTTON_E) {
      return std::shared_ptr<gameObject>(
          new button(pos, scale, textureMap, firstKey, *this, prio, target));
    } else if (objectType == objectTypes_E::BACKGROUND_E) {
      return std::shared_ptr<gameObject>(
          new background(pos, scale, textureMap, firstKey, prio));
    } else if (objectType == objectTypes_E::TITLECARD_E) {
      return std::shared_ptr<gameObject>(
          new titlecard(pos, scale, textureMap, *this, firstKey, prio));
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
  };
}

void objectStorage::factorNewGameState(std::string stateFileName) {
  std::ifstream inputFile(stateFileName);
  std::string storageType;
  try {
    while (true) {
      if (inputFile.peek() == EOF) {
        throw end_of_file("end of file reached");
      }
      std::cout << "Pushback1" << std::endl;
      allVectors[stateFileName]->push_back(factorObject(inputFile));
      std::cout << "Pushback2" << std::endl;
    }
  } catch (end_of_file& e) {
    std::cerr << e.what() << std::endl;
  } catch (problem& e) {
    std::cerr << e.what() << std::endl;
  }
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
