#ifndef _ANIMATION_HPP
#define _ANIMATION_HPP

#include <SFML/Graphics.hpp>

class Animation {
public:

	Animation( sf::Vector2f position, int frame = 0, int counter = 0);

	void draw( sf::RenderWindow & window ) ;

	void move( sf::Vector2f delta );

    void ineract(sf::Vector2f target);

	void Set_Frame(int max_frame, int row);

private:
	sf::RectangleShape rectangle;
	sf::Sprite Sprite;
	sf::Texture Texture;
	sf::Vector2f position;
	int frame;
	int counter;
};

#endif
