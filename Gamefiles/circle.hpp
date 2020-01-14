#ifndef _CIRCLE_HPP
#define _CIRCLE_HPP
#include <SFML/Graphics.hpp>
#include "gameObject.hpp"
#include <iostream>
#include "collisionBox.hpp"
#include "interactionBox.hpp"

class circleObject : public gameObject {
public:

	circleObject( sf::Vector2f position, float size):
	    position( position ),
	    size( size ),
		circleInteractionBox(position, sf::Vector2f(size*2, size*2)){
            objectCircle.setPosition(position);
            objectCircle.setRadius(size);
			circleCollisionBox.setBoxes(objectCircle.getGlobalBounds());
			circleTexture = new sf::Texture;
			circleTexture->loadFromFile(std::string("cthulhuHead.png"));
			objectCircle.setTexture(circleTexture);
        };
	~circleObject(){}

	void move( sf::Vector2f delta) override{
        position+= delta;
        objectCircle.setPosition(objectCircle.getPosition() + delta);
		circleCollisionBox.move(delta);
		circleInteractionBox.move(delta);
    };
	void draw( sf::RenderWindow & window ){
        window.draw(objectCircle);
		circleCollisionBox.draw(window);
		circleInteractionBox.draw(window);
    };

private:
	sf::Vector2f position;
	float size;
	CollisionBox circleCollisionBox;
	interactionBox circleInteractionBox;	
	sf::Texture* circleTexture;
	sf::CircleShape objectCircle;
};

#endif
