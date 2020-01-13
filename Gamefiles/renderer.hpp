#ifndef _RENDERER_HPP
#define _RENDERER_HPP
#include "SFML/Graphics.hpp"
#include "gameStorage.hpp"
#include "circle.hpp"

class renderer{
private:
    sf::RenderWindow& window;
    gameStorage& storage;

public:
    renderer(sf::RenderWindow & window, gameStorage& storage):
    window(window),
    storage{storage}
    {
        storage.add( std::shared_ptr<gameObject>( new circleObject(sf::Vector2f(20.0, 20.0), 30.0)));
    }

    void  draw(){
        for(auto &i : storage.get()){
            i->draw(window);
        }
    }

    void update(){
        for(auto& i : storage.get()){
            i->update();
        }
    }


    gameStorage & getStorage(){return storage;}

};


#endif