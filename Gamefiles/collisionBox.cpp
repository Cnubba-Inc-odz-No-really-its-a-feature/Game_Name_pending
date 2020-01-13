#include "collisionBox.hpp"
#include "SFML/Graphics.hpp"

CollisionBox::CollisionBox(){}

void CollisionBox::setBoxes(sf::FloatRect Host){
        Left.setSize(sf::Vector2f(5.0, Host.height-10.0));
        Left.setPosition(sf::Vector2f(Host.left, Host.top+5.0));
        Left.setFillColor(sf::Color::Red);
        Top.setSize(sf::Vector2f(Host.width -9.0, 5.0));
        Top.setPosition(sf::Vector2f(Host.left +4.5, Host.top));
        Top.setFillColor(sf::Color::White);
        Right.setSize(sf::Vector2f(5.0, Host.height - 10.0));
        Right.setPosition(sf::Vector2f((Host.left+Host.width) - 5.0, Host.top +5.0));
        Right.setFillColor(sf::Color::Red);
        Bottom.setSize(sf::Vector2f(Host.width - 9.0, 5.0));
        Bottom.setPosition(sf::Vector2f(Host.left + 4.5, (Host.top + Host.height) - 5));
        Bottom.setFillColor(sf::Color::White);
}

void CollisionBox::draw( sf::RenderWindow & window){
    window.draw(Left);
    window.draw(Top);
    window.draw(Right);
    window.draw(Bottom);
}

void CollisionBox::move( sf::Vector2f delta ){
        Left.setPosition(Left.getPosition() + delta);
        Top.setPosition(Top.getPosition() + delta);
        Right.setPosition(Right.getPosition() + delta);
        Bottom.setPosition(Bottom.getPosition() + delta);
}


E_Box CollisionBox::intersect(sf::FloatRect RectExt){
        if(Left.getGlobalBounds().intersects(RectExt)){
            return E_Box::WALL_L;
        }else if( Top.getGlobalBounds().intersects(RectExt)){
            return E_Box::WALL_T;
        }else if( Right.getGlobalBounds().intersects(RectExt)){
            return E_Box::WALL_R;
        }else if( Bottom.getGlobalBounds().intersects(RectExt)){
            return E_Box::WALL_B;
        }
        else{
            return E_Box::NO_INTERSECT;
        }

    }
