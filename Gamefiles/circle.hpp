#ifndef _CIRCLE_HPP
#define _CIRCLE_HPP
#include <SFML/Graphics.hpp>
#include "gameObject.hpp"
#include <iostream>

class circleObject : public gameObject {
public:

	circleObject( sf::Vector2f position, sf::Vector2f size, std::map<std::string, sf::Texture> textureMap):
	    position( position ),
	    size( size ),
		textureMap(textureMap){
            circleSprite.setPosition(position);
			circleSprite.setScale(size);
			circleSprite.setTexture((textureMap.begin())->second);
        };
	~circleObject(){}

	void move( sf::Vector2f delta) override{
        position+= delta;
        circleSprite.setPosition(circleSprite.getPosition() + delta);
    };
	void draw( sf::RenderWindow & window ){
        window.draw(circleSprite);
    };

private:
	sf::Vector2f position;
	sf::Vector2f size;
	std::map<std::string, sf::Texture> textureMap;
	sf::Sprite circleSprite;
};

#endif
