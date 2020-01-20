#include "factory.hpp"

factory::factory(objectStorage &storage, sf::RenderWindow & window): 
        storage(storage),
        window(window)
    {}

std::shared_ptr<gameObject> factory::factorObject(std::ifstream & inputFile){
    objectTypes_E objectType;
    sf::Vector2f pos;
    sf::Vector2f scale;
    std::string idString;
    std::map<std::string, sf::Texture> textureMap;
    std::string textureMapKey;
    std::string textureFile;
    sf::Texture objectTexture;
    char textureBind;
    int prio;

    try{
        inputFile >> objectType >> pos >> scale >> prio;
        try{
            while(true){
                inputFile >> textureMapKey;
                inputFile >> textureFile;
                objectTexture.loadFromFile(textureFile);
                textureMap[textureMapKey] = objectTexture;
                inputFile>> textureBind;
                if(! (textureBind == ',')){
                    throw end_of_textures("end of textures reached");
                }
            }
        }catch(end_of_textures & e){std::cerr<<e.what() <<std::endl;};

        if(objectType == objectTypes_E::CHARACTER_E){
            return std::shared_ptr<gameObject>(new character(pos, scale, textureMap, window, prio));
        }else if(objectType == objectTypes_E::TESTSPRITE_E){
            std::cout<<"textSpriteMade" << std::endl;
            return std::shared_ptr<gameObject>(new textureSprite(pos, scale, textureMap, prio));
        }else if(objectType == objectTypes_E::CHEST_E){
            std::cout<<"chest begin made" << std::endl;
            return std::shared_ptr<gameObject>(new chest(pos, scale, textureMap, prio));
        }else if(objectType == objectTypes_E::BUTTON_E){
            std::cout<<"Button begin made" << std::endl;
            return std::shared_ptr<gameObject>(new button(pos, scale, textureMap, prio));
        }else if(objectType == objectTypes_E::BACKGROUND_E){
            std::cout<<"Background begin made" << std::endl;
            return std::shared_ptr<gameObject>(new background(pos, scale, textureMap, prio));
        }else if(objectType == objectTypes_E::TITLECARD_E){
            std::cout<<"Titlecard begin made" << std::endl;
            return std::shared_ptr<gameObject>(new titlecard(pos, scale, textureMap, prio, storage));
        }
    
        throw invalid_type("invalid type found");

    }catch(invalid_type& e){std::cerr<< e.what() <<std::endl; throw invalid_type(e.what());
    }catch(unknown_pos &e){std::cerr<<e.what() <<std::endl; throw unknown_pos('p');
    }catch(end_of_file & e){throw end_of_file("end of file reached");};
}

void factory::factorNewGameState(std::string stateFileName){
    storage.title.get()->clear();
    storage.menu.get()->clear();
    storage.game.get()->clear();
    std::ifstream inputFile(stateFileName);
    std::string storageType;
    try{
        while(true){
            inputFile >> storageType;
            if(storageType == ""){
                throw end_of_file("end of file reached");
            }
            if(storageType == "Game"){
                storage.game.get()->push_back(factorObject(inputFile));
            }else if(storageType == "Menu"){
                storage.game.get()->push_back(factorObject(inputFile));
            }else if(storageType == "Character"){
                storage.character1 = factorObject(inputFile);
            }
            else if(storageType == "Title"){
                storage.title.get()->push_back(factorObject(inputFile));
            }

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


