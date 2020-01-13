#ifndef _COLLISIONBOX_HPP
#define _COLLISIONBOX_HPP
#include "SFML/Graphics.hpp"
enum E_Box{WALL_L, WALL_T, WALL_R, WALL_B, NO_INTERSECT};

class CollisionBox{
private:
    sf::RectangleShape Left;
    sf::RectangleShape Top;
    sf::RectangleShape Right;
    sf::RectangleShape Bottom;
    
public:

    CollisionBox();


    void setBoxes(sf::FloatRect Host);
    

    void draw(  sf::RenderWindow & window);

    void move( sf::Vector2f delta);

    E_Box intersect(sf::FloatRect RectExt);

   

};


#endif