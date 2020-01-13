#ifndef _CIRCLE_HPP
#define _CIRCLE_HPP
#include <SFML/Graphics.hpp>
#include "gameObject.hpp"
#include <iostream>
#include "collisionBox.hpp"

class circleObject : public gameObject {
public:

	circleObject( sf::Vector2f position, float size):
	    position( position ),
	    size( size ){
            objectCircle.setPosition(position);
            objectCircle.setRadius(size);
			circleCollisionBox.setBoxes(objectCircle.getGlobalBounds());
        };
	~circleObject(){}

	void move( sf::Vector2f delta) override{
        position+= delta;
        objectCircle.setPosition(objectCircle.getPosition() + delta);
		circleCollisionBox.move(delta);
    };
	void draw( sf::RenderWindow & window ){
        window.draw(objectCircle);
		circleCollisionBox.draw(window);
    };

private:
	sf::Vector2f position;
	float size;
	CollisionBox circleCollisionBox;
	sf::CircleShape objectCircle;
};

#endif
