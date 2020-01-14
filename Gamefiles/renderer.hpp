#ifndef _RENDERER_HPP
#define _RENDERER_HPP
#include "SFML/Graphics.hpp"
#include "objectStorage.hpp"
#include "circle.hpp"
#include "floor.hpp"

class renderer{
private:
    
    sf::RenderWindow& window;
    objectStorage &renderStorage;
public:
    
    renderer(sf::RenderWindow & window, objectStorage &renderStorage):
    window(window),
    renderStorage(renderStorage){
        renderStorage.game.push_back(std::shared_ptr<gameObject>( new circleObject(sf::Vector2f(20.0, 540.0), 30.0)));

        renderStorage.game.push_back(std::shared_ptr<gameObject>( 
            new floorObject(sf::Vector2f(20.0, 600.0), sf::Vector2f(1600.0, 300.0), std::string("floorSprite1.png"))));

    }

    void update(){}

    void  draw(){
        for(auto &i : renderStorage.game){
            i->draw(window);
        }
    }
};


#endif