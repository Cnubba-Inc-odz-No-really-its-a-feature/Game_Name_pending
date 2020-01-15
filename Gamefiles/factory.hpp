#ifndef _FACTORY_HPP_
#define _FACTORY_HPP_

#include "gameObject.hpp"
#include "objectStorage.hpp"
#include "fstream"
#include "operators.hpp"


class textureSprite : public gameObject{
protected:
    sf::Sprite sprite;
    sf::Texture spriteTexture;
public:
    textureSprite(sf::Vector2f pos, int prio, sf::Vector2f size, sf::Texture &texture):spriteTexture(texture){
        sprite.setPosition(pos);
        sprite.setScale(size.x, size.y);
        sprite.setTexture(spriteTexture);
    }

    void draw(sf::RenderWindow& window){
        window.draw(sprite);
        // std::cout<<"texture drawn" << std::endl;
    }

    void move(sf::Vector2f delta){
        sprite.setPosition(sprite.getPosition()+delta);
    }
};

class titleCard : public textureSprite{
private:
    int framecount = 0;
    objectStorage & storage;
public:
    titleCard(sf::Vector2f pos, int prio,sf::Vector2f size, sf::Texture &texture, objectStorage & storage):textureSprite(pos, prio, size, texture), storage(storage){}

    void update(){
        framecount++;
        // std::cout << "Framecount: " << framecount << std::endl;
        if(framecount < 1000){
            return;
        }
        if(framecount < 2000){
            sprite.setPosition(sprite.getPosition()-sf::Vector2f(0,0.25));
            return;
        }
        if(framecount > 2500){
            storage.setActive("Menu");
            return;
        }
    }
};

class factory{
private:
    std::ifstream inputFile;
    objectStorage &storage;

public:
    factory(objectStorage &storage): storage(storage){
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
            // std::cout<<"1 try done" << std::endl;
        }}catch(...){}
        inputFile.close();
        inputFile.open("objects.txt");
        sf::Vector2f pos;
        sf::Vector2f size;
        int prio;
        std::string idString;
        try{while (inputFile >> pos >> size >> prio >> idString >> nameTexture)
        {
            sf::Texture* pointer = storage.textureMap[nameTexture].get();
            auto texture = *pointer;
            // std::shared_ptr<textureSprite> obj(new textureSprite(pos, size, texture));
            if(idString == "Menu"){
                std::shared_ptr<textureSprite> obj(new textureSprite(pos, prio ,size, texture));
                storage.menu.get()->push_back(obj);
                // std::cout<<"thrown in menu" << std::endl;
            }
            else if (idString == "Game")
            {
                std::shared_ptr<textureSprite> obj(new textureSprite(pos, prio, size, texture));
                // std::cout<<"added to gamestoragee" <<std::endl;
                storage.game.get()->push_back(obj);
            }
            else if (idString == "Title")
            {
                // std::cout<<"added to titlestorage1" <<std::endl;
                std::shared_ptr<titleCard> obj(new titleCard(pos, prio, size, texture, storage));
                // std::cout<<"added to titlestorage2" <<std::endl;
                storage.title.get()->push_back(obj);
            }
            else if (idString == "Background")
            {
                // std::cout<<"added to titlestorage1" <<std::endl;
                std::shared_ptr<textureSprite> obj(new textureSprite(pos, prio, size, texture));
                // std::cout<<"added to titlestorage2" <<std::endl;
                storage.title.get()->push_back(obj);
            }
            // std::cout<<"1 try done" << std::endl;
        }}catch(...){/*std::cout<<"caught" << std::endl;*/}
        



    };  

    void saveState()
    {
        std::cout<< "TODO: not yet implemented, saveState" << std::endl; 
        return;
    };
};


#endif // _FACTORY_HPP_