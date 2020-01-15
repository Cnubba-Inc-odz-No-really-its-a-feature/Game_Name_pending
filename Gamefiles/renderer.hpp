#ifndef _RENDERER_HPP
#define _RENDERER_HPP
#include "SFML/Graphics.hpp"
#include "objectStorage.hpp"
#include "circle.hpp"

class renderer{
private:
    sf::RenderWindow& window;
    objectStorage& renderStorage;

public:
    renderer(sf::RenderWindow & window, objectStorage& renderStorage):
    window(window),
    renderStorage{renderStorage}
    {}

    void  draw(){
        for(auto &i : *renderStorage.game){
            i->draw(window);
        }
    }

    void update(){
        for(auto i : *renderStorage.menu){
            i->update();
        }
    }


    objectStorage & getStorage(){return renderStorage;}

};


#endif