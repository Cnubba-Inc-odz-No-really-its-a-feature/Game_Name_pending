#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.hpp"
#include <unistd.h>

Animation::Animation( sf::Vector2f position, int frame, int counter ) :
	rectangle(sf::RectangleShape()),
	Sprite(sf::Sprite()),
	position{ position },
	frame(frame),
	counter(counter)

{
	Texture.loadFromFile("skeleton.png");
	Sprite.setTexture(Texture);
	Sprite.setScale(5,5);
}

void Animation::Set_Frame(int max_frame, int row){
	if(counter > 10) {counter = 0; frame++;}
	if(max_frame < frame) frame = 0;
	Sprite.setTextureRect(sf::IntRect(64*frame, 64*row, 64, 64));
	counter++;
}

void Animation::move( sf::Vector2f delta ) {
	if(delta.x < 0) Set_Frame(8, 9);
	if(delta.x > 0) Set_Frame(8, 11);
 	position += delta;
}

void Animation::draw( sf::RenderWindow & window  )  {
	Sprite.setPosition(position);
	window.draw(Sprite);
	
}

void Animation::ineract(sf::Vector2f target) {
    if(Sprite.getGlobalBounds().contains(target)){
		Sprite.setScale(5.3,5.3);
    }
	else Sprite.setScale(5,5);

}