#ifndef _RENDERER_HPP
#define _RENDERER_HPP
#include "objectStorage.hpp"
#include "fightController.hpp"

///\brief
/// Function nesessery for sorting vectors by priority 
bool objSort(const std::shared_ptr<gameObject> & lhs, const std::shared_ptr<gameObject> & rhs);

///\brief
/// Draws all active objects every frame, ensures the correct order of drawing  and does the crossfading
class renderer{
private:
    sf::RenderWindow& gameWindow;
    objectStorage& renderObjectStorage;
    fightController& fightControl;
    sf::RectangleShape fade;
    uint16_t color;
    bool switchActive = false;
    // std::priority_queue<std::shared_ptr<gameObject>, std::vector<std::shared_ptr<gameObject>>> queue;
public:
    ///\brief
    /// constructor of the renderer.
    renderer(sf::RenderWindow & gameWindow, objectStorage& renderObjectStorage, fightController& fightControl):
    fightControl{fightControl},
    gameWindow(gameWindow),
    renderObjectStorage{renderObjectStorage}
    {
        fade.setSize( sf::Vector2f(1920, 1080));
        color = 0;
    }

    ///\brief
    /// Draws all active objects every frame, ensures the correct order of drawing  and does the crossfading
    void draw(){
        std::sort(renderObjectStorage.getActive()->begin(), renderObjectStorage.getActive()->end(), objSort);
        for(auto &i : *renderObjectStorage.getActive()){
            i->draw(gameWindow);
        }



        //VOOR KAART TESTS
        //for(auto &i : renderObjectStorage.cardsInHand){
        //    i->draw(gameWindow);
        //}
        if(renderObjectStorage.keyActive.at(0) == 'd'){
            renderObjectStorage.deckEditor.draw(gameWindow);
        }

        if(renderObjectStorage.keyActive.at(0) == 'c'){
            renderObjectStorage.cardHand.draw(gameWindow);
            fightControl.draw(gameWindow);
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

    ///\brief
    /// Calls update on all active objects, and the char if nesessery
    void update(){
        // auto tmp = renderObjectStorage.getActive();
        for(auto i : *renderObjectStorage.getActive()){
            i->update();
        }
        if(renderObjectStorage.keyActive.at(0) == 'r'){
            renderObjectStorage.character1->update();
        }
        
    }

    ///\brief
    /// returns by reference the held objectStorage
    objectStorage & getStorage(){return renderObjectStorage;}

};


#endif