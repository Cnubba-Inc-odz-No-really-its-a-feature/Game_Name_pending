#ifndef _RENDERER_HPP
#define _RENDERER_HPP
#include "SFML/Graphics.hpp"
#include "gameStorage.hpp"
#include "circle.hpp"
class renderer{
private:
    
    sf::RenderWindow& window;
public:
    gameStorage renderStorage;
    renderer(sf::RenderWindow & window):
    window(window){
        renderStorage.add( std::shared_ptr<gameObject>( new circleObject(sf::Vector2f(20.0, 20.0), 30.0)));
    }

    void update(){}

    void  draw(){
        for(auto &i : renderStorage.get()){
            i->draw(window);
        }
    }

    gameStorage & getStorage(){return renderStorage;}


};


#endif