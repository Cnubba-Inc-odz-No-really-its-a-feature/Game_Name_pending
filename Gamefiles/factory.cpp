#include "factory.hpp"

factory::factory(sf::RenderWindow & window): 
        window(window)
    {};

std::shared_ptr<gameObject> factory::factorObject(std::ifstream & inputFile){
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

    try{
        inputFile >> objectType >> pos >> scale >> prio;
        try{
            bool firstrun = true;
            if(objectType == DOOR_E){
                inputFile >> target;
            } 
            while(true){
                inputFile >> textureMapKey;
                inputFile >> textureFile;
                objectTexture.loadFromFile(textureFile);
                textureMap[textureMapKey] = objectTexture;
                inputFile >> textureBind;
                if( firstrun ){
                    firstKey = textureMapKey;
                    firstrun = false;
                }
                if(! (textureBind == ',')){
                    throw end_of_textures("end of textures reached");
                }
            }
        }catch(end_of_textures & e){std::cerr<<e.what() <<std::endl;};

        if(objectType == objectTypes_E::CHARACTER_E){
            return std::shared_ptr<gameObject>(new character(pos, scale, textureMap, window, firstKey, prio));
        }else if(objectType == objectTypes_E::TESTSPRITE_E){
            std::cout<< "textSpriteMade " << firstKey << std::endl;
            return std::shared_ptr<gameObject>(new textureSprite(pos, scale, textureMap, firstKey, prio));
        }else if(objectType == objectTypes_E::CHEST_E){
            std::cout<<"chest begin made " << firstKey << std::endl;
            return std::shared_ptr<gameObject>(new chest(pos, scale, textureMap, firstKey, prio));
        }else if(objectType == objectTypes_E::DOOR_E){
            std::cout<<"door begin made " << firstKey << std::endl;
            return std::shared_ptr<gameObject>(new door(pos, scale, textureMap, firstKey, storage, prio, target));
        }else if(objectType == objectTypes_E::BUTTON_E){
            std::cout<<"Button begin made " << firstKey << std::endl;
            return std::shared_ptr<gameObject>(new button(pos, scale, textureMap, firstKey, storage, prio));
        }else if(objectType == objectTypes_E::BACKGROUND_E){
            std::cout<<"Background begin made " << firstKey << std::endl;
            return std::shared_ptr<gameObject>(new background(pos, scale, textureMap, firstKey, prio));
        }else if(objectType == objectTypes_E::TITLECARD_E){
            std::cout<<"Titlecard begin made " << firstKey << std::endl;
            return std::shared_ptr<gameObject>(new titlecard(pos, scale, textureMap, storage, firstKey, prio));
        }
    
        throw invalid_type("invalid type found");

    }catch(invalid_type& e){std::cerr<< e.what() <<std::endl; throw invalid_type(e.what());
    }catch(unknown_pos &e){std::cerr<<e.what() <<std::endl; throw unknown_pos('p');
    }catch(end_of_file & e){throw end_of_file("end of file reached");};
}

void factory::factorNewGameState(std::string stateFileName){
    std::ifstream inputFile(stateFileName);
    std::string storageType;

    try{
        while(true){
            if(inputFile.peek() == EOF){
                throw end_of_file("end of file reached");
            }
            storage.allVectors[stateFileName]->push_back(factorObject(inputFile));
        } 
    }catch(end_of_file & e){
        std::cerr << e.what() << std::endl;
    }catch(problem & e){
        std::cerr << e.what() << std::endl;
    }
}

void factory::factorMainCharacter(){
    try{
        std::ifstream characterFile("mainCharacter.txt");
        std::string storageType;
        characterFile >> storageType;
        if(storageType != "Character"){
            throw invalid_type("invalid CharacterType found");
        }
        storage.character1 = factorObject(characterFile);

    }catch(end_of_file & e){
    }catch(problem& e){std::cerr<<e.what()<<std::endl;}   
}


