#ifndef _CIRCLE_HPP
#define _CIRCLE_HPP
#include <SFML/Graphics.hpp>
#include "gameObject.hpp"
#include <iostream>

class circleObject : public gameObject {
public:

	circleObject( sf::Vector2f position, float size):
	    position( position ),
	    size( size ){
            objectCircle.setPosition(position);
            objectCircle.setRadius(size);
        };
	~circleObject(){}

	void move( sf::Vector2f delta) override{
        position+= delta;
        objectCircle.setPosition(objectCircle.getPosition() + delta);
    };
	void draw( sf::RenderWindow & window ){
        window.draw(objectCircle);
    };

private:
	sf::Vector2f position;
	float size;
	sf::CircleShape objectCircle;
};

#endif
