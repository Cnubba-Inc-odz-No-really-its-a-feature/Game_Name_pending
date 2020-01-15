#ifndef _FACTORY_HPP_
#define _FACTORY_HPP_

#include "gameObject.hpp"
#include "objectStorage.hpp"
#include "fstream"
#include "operators.hpp"
#include "character.hpp"

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
        //generate all objects and add them to the storage
        inputFile.open("texture.txt");
        std::string nameTexture;
        try{while ( inputFile >> nameTexture)
        {
            //auto tmp = sf::Image();
            //tmp.loadFromFile(nameTexture);
            std::shared_ptr<sf::Texture> texture(new sf::Texture);
            texture->loadFromFile(nameTexture);
            storage.textureMap.insert({nameTexture, texture});
            std::cout<<"1 try done" << std::endl;
        }}catch(...){}
        inputFile.close();
        inputFile.open("objects.txt");
        sf::Vector2f pos;
        sf::Vector2f size;
        std::string idString;
        try{while (inputFile >> pos >> size >> idString >> nameTexture)
        {
            //auto pointer = storage.textureMap[nameTexture].get();
            //auto texture = *pointer;
            std::shared_ptr<gameObject> obj(new character(pos, size, nameTexture, window));

            if(idString == "Menu"){
                //storage.menu.get()->push_back(obj);
                std::cout<<"thrown in menu" << std::endl;
            }
            else if (idString == "Game")
            {
                std::cout<<"added to gamestoragee" <<std::endl;
                storage.game.get()->push_back(obj);
            }else if (idString == "Character"){
                std::shared_ptr<character> obj(new character(pos, size, nameTexture, window));
                storage.character1 = obj;
                std::cout<<"character made" << std::endl;
            }
            std::cout<<"1 try done" << std::endl;
        }}catch(...){std::cout<<"caught" << std::endl;}
        



    };  

    void saveState()
    {
        std::cout<< "TODO: not yet implemented, saveState" << std::endl; 
        return;
    };
};


#endif // _FACTORY_HPP_