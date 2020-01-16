#ifndef _FACTORY_HPP_
#define _FACTORY_HPP_

#include "gameObject.hpp"
#include "objectStorage.hpp"
#include "fstream"
#include "operators.hpp"
#include "character.hpp"
#include <map>

// class textureSprite : public gameObject{
// private:
//     sf::Sprite sprite;
//     sf::Texture spriteTexture;
// public:
//     textureSprite(sf::Vector2f pos, sf::Vector2f size, sf::Texture &texture):spriteTexture(texture){
//         sprite.setPosition(pos);
//         sprite.setScale(size.x, size.y);
//         sprite.setTexture(spriteTexture);
//     }

//     void draw(sf::RenderWindow& window){
//         window.draw(sprite);
//         std::cout<<"texture drawn" << std::endl;
//     }

//     void move(sf::Vector2f delta){
//         sprite.setPosition(sprite.getPosition()+delta);
//     }
// };

class factory{
private:
    std::ifstream inputFile;
    objectStorage &storage;
    sf::RenderWindow & window;
public:
    factory(objectStorage &storage, sf::RenderWindow & window): 
        storage(storage),
        window(window)
    {
        // //generate all objects and add them to the storage
        
        // sf::Vector2f pos;
        // sf::Vector2f size;
        // std::string idString;
        // try{while (inputFile >> pos >> size >> idString >> nameTexture)
        // {
        //     //auto pointer = storage.textureMap[nameTexture].get();
        //     //auto texture = *pointer;
        //     std::shared_ptr<gameObject> obj(new character(pos, size, nameTexture, window));

        //     if(idString == "Menu"){
        //         //storage.menu.get()->push_back(obj);
        //         std::cout<<"thrown in menu" << std::endl;
        //     }
        //     else if (idString == "Game")
        //     {
        //         std::cout<<"added to gamestoragee" <<std::endl;
        //         storage.game.get()->push_back(obj);
        //     }else if (idString == "Character"){
        //         std::shared_ptr<character> obj(new character(pos, size, nameTexture, window));
        //         storage.character1 = obj;
        //         std::cout<<"character made" << std::endl;
        //     }
        //     std::cout<<"1 try done" << std::endl;
        // }}catch(...){std::cout<<"caught" << std::endl;}
    }

std::shared_ptr<gameObject> factorObject(std::ifstream & inputFile){
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


    void factorObjectsFromFile(std::string inputFileName){
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

    void saveState()
    {
        std::cout<< "TODO: not yet implemented, saveState" << std::endl; 
        return;
    };
};


#endif // _FACTORY_HPP_