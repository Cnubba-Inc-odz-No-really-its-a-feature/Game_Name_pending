#ifndef _RENDERER_HPP
#define _RENDERER_HPP
#include "objectStorage.hpp"

bool objSort(const std::shared_ptr<gameObject> & lhs, const std::shared_ptr<gameObject> & rhs);

class renderer{
private:
    sf::RenderWindow& gameWindow;
    objectStorage& renderObjectStorage;
    sf::RectangleShape fade;
    uint16_t color;
    bool switchActive = false;
    // std::priority_queue<std::shared_ptr<gameObject>, std::vector<std::shared_ptr<gameObject>>> queue;
public:
    renderer(sf::RenderWindow & gameWindow, objectStorage& renderObjectStorage):
    gameWindow(gameWindow),
    renderObjectStorage{renderObjectStorage}
    {
        fade.setSize( sf::Vector2f(1920, 1080));
        color = 0;
    }

    void draw(){
        std::sort(renderObjectStorage.getActive()->begin(), renderObjectStorage.getActive()->end(), objSort);
        for(auto &i : *renderObjectStorage.getActive()){
            i->draw(gameWindow);
        }



        //VOOR KAART TESTS
        //for(auto &i : renderObjectStorage.cardsInHand){
        //    i->draw(gameWindow);
        //}
        if(renderObjectStorage.storageDeck.fightActive){

            renderObjectStorage.storageDeck.DrawHand(gameWindow);
        }



        if(renderObjectStorage.keyActive.at(0) == 'r'){
            renderObjectStorage.character1->draw(gameWindow);
        }

        if(renderObjectStorage.swappedActive){
            if(!switchActive){
                fade.setFillColor(sf::Color(0,0,0,color));
                color += 15;
                gameWindow.draw(fade);
                if(color >= 255){
                    renderObjectStorage.tmpNewActive();
                    switchActive = true;
                }
            }else if(switchActive){
                fade.setFillColor(sf::Color(0,0,0,color));
                color -= 15;
                gameWindow.draw(fade);
                if(color <= 0){
                    switchActive = false;
                    renderObjectStorage.swappedActive = false;
                }
            }
        }
    }

    void update(){
        // auto tmp = renderObjectStorage.getActive();
        for(auto i : *renderObjectStorage.getActive()){
            i->update();
        }
        if(renderObjectStorage.keyActive.at(0) == 'r'){
            renderObjectStorage.character1->update();
        }
        
    }


    objectStorage & getStorage(){return renderObjectStorage;}

};


#endif