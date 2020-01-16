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
                std::cout<<"new texture" <<std::endl;
                inputFile >> textureMapKey;
                inputFile >> textureFile;
                objectTexture.loadFromFile(textureFile);
                textureMap[textureMapKey] = objectTexture;
                std::cout<<"before texturebind"  <<std::endl;
                inputFile>> textureBind;
                if(! (textureBind == ',')){
                    throw end_of_textures("end of textures reached");
                }
                std::cout<<"texture made" << std::endl;
            }
        }catch(end_of_textures & e){std::cerr<<e.what() <<std::endl;};

        if(objectType == objectTypes_E::CHARACTER_E){
            return std::shared_ptr<gameObject>(new character(pos, scale, textureMap, window, prio));
        }
    
        throw invalid_type("invalid type found");

    }catch(invalid_type& e){std::cerr<< e.what() <<std::endl; throw invalid_type(e.what());
    }catch(unknown_pos &e){std::cerr<<e.what() <<std::endl; throw unknown_pos('p');
    }catch(end_of_file & e){throw end_of_file("end of file reached");};
}


void factory::factorObjectsFromFile(std::string inputFileName){
    std::ifstream inputFile(inputFileName);
    std::string storageType;
    try{
        while(true){
            inputFile >> storageType;
            if(storageType == ""){
                throw end_of_file("end of file reached");
            }
            if(storageType == "Game"){
                std::cout<<"added to gamestorage" <<std::endl;
                storage.game.get()->push_back(factorObject(inputFile));
            }else if(storageType == "Menu"){
                std::cout<<"added to gamestoragee" <<std::endl;
                storage.game.get()->push_back(factorObject(inputFile));
            }else if(storageType == "Character"){
                storage.character1 = factorObject(inputFile);
            }
        }
    }catch(end_of_file & e){
        std::cerr << e.what() << std::endl;
    }catch(problem & e){
        std::cerr << e.what() << std::endl;
    }
}  

void factory::saveState(){
    std::cout<< "TODO: not yet implemented, saveState" << std::endl; 
    return;
}