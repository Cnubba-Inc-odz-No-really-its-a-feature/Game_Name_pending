#ifndef _RENDERER_HPP
#define _RENDERER_HPP
#include "SFML/Graphics.hpp"
#include "objectStorage.hpp"
//#include "circle.hpp"

bool objSort(const std::shared_ptr<gameObject> & lhs, const std::shared_ptr<gameObject> & rhs);

class renderer{
private:
    sf::RenderWindow& gameWindow;
    objectStorage& renderObjectStorage;
    // std::priority_queue<std::shared_ptr<gameObject>, std::vector<std::shared_ptr<gameObject>>> queue;
public:
    renderer(sf::RenderWindow & gameWindow, objectStorage& renderObjectStorage):
    gameWindow(gameWindow),
    renderObjectStorage{renderObjectStorage}
    {}

    void  draw(){
        std::sort(renderObjectStorage.getActive().get()->begin(), renderObjectStorage.getActive().get()->end(), objSort);
        for(auto &i : *renderObjectStorage.getActive()){
            i->draw(gameWindow);
    }
    if(renderObjectStorage.keyActive == "Game"){
        renderObjectStorage.character1.get()->draw(gameWindow);}
    }

    void update(){
        for(auto i : *renderObjectStorage.getActive()){
            i->update();
        }
        renderObjectStorage.character1->update();
    }


    objectStorage & getStorage(){return renderObjectStorage;}

};


#endif