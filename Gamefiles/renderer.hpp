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
    {
        std::cout<<"rendererConstructor entered" << std::endl;
        //renderStorage.game->push_back(std::shared_ptr<gameObject>( new circleObject(sf::Vector2f(20.0, 20.0), 30.0)));
        std::cout<<"circle is aangemaakt" << std::endl;}

    void  draw(){
        for(auto &i : *renderStorage.game){
            i->draw(window);
            std::cout<<"object drawn" << std::endl;
        }

        std::cout<<"all objects have been drawn" << std::endl;
    }

    void update(){
        for(auto i : *renderStorage.menu){
            i->update();
        }
    }


    objectStorage & getStorage(){return renderStorage;}

};


#endif