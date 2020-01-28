#include "popup.hpp"

popup::popup(const sf::Vector2f & anker, std::string textureString):anker(anker)
{//select some random cards

    Options.push_back(factorCard(std::rand()%10)); 
    Options.push_back(factorCard(std::rand()%10)); 
    Options.push_back(factorCard(std::rand()%10)); 
    Options[0]->setPosition(sf::Vector2f(anker.x-100, anker.y-300));
    Options[1]->setPosition(sf::Vector2f(anker.x+100, anker.y-300));
    Options[2]->setPosition(sf::Vector2f(anker.x+300, anker.y-300));
    texture.loadFromFile("gameAssets/popupBackground.png");
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(anker.x-200, anker.y-350));
}

int popup::update(){
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(Options[0]->getSprite().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition()))){
            std::cout << "Pressed" << std::endl;
            return Options[0]->getCardID();
        }
        if(Options[1]->getSprite().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition()))){
            std::cout << "Pressed" << std::endl;
            return Options[1]->getCardID();
        }
        if(Options[2]->getSprite().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition()))){
            std::cout << "Pressed" << std::endl;
            return Options[2]->getCardID();
        }
    }
    return -1;
};

void popup::interact(){};

void popup::draw(sf::RenderWindow& gameWindow){
    gameWindow.draw(sprite);
    for(auto i : Options){
        i->draw(gameWindow);
    }
};