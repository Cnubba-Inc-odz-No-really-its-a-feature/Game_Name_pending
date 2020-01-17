#ifndef _RENDERER_HPP
#define _RENDERER_HPP
#include "SFML/Graphics.hpp"
#include "objectStorage.hpp"
//#include "circle.hpp"

class renderer{
private:
    sf::RenderWindow& window;
    objectStorage& renderStorage;
    std::priority_queue<std::shared_ptr<gameObject>, std::vector<std::shared_ptr<gameObject>>> queue;
public:
    renderer(sf::RenderWindow & window, objectStorage& renderStorage):
    window(window),
    renderStorage{renderStorage}
    {
        std::cout<<"rendererConstructor entered" << std::endl;
        //renderStorage.game->push_back(std::shared_ptr<gameObject>( new circleObject(sf::Vector2f(20.0, 20.0), 30.0)));
        //std::cout<<"circle is aangemaakt" << std::endl;
    }

    void  draw(){
        // std::cout << "curr gamestate: " << renderStorage.keyActive << std::endl;
        for(auto &i : *renderStorage.getActive()){
            queue.push(i);
            // std::cout << "pushed to queue" << std::endl;
            //i->draw(window);
    }

    while(queue.size()){
        std::cout << "prio: " << queue.top()->priority << std::endl;
        queue.top()->draw(window);
        queue.pop();
        // std::cout << "popped from queue" << std::endl;
    }
        // renderStorage.character1.get()->draw(window);
    }

    void update(){
        for(auto i : *renderStorage.getActive()){
            i->update();
        }
    }


    objectStorage & getStorage(){return renderStorage;}

};


#endif