#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.hpp"

sf::Vector2f Vector2f_from_Vector2i( sf::Vector2i rhs ){
	return sf::Vector2f(
		static_cast< float >( rhs.x ),
		static_cast< float >( rhs.y )
	);
}


int main( int argc, char *argv[] ){
	float const acceleration = 10;
	sf::RenderWindow window{ sf::VideoMode{ 2000, 800 }, "Idle" };
	Animation Character{ sf::Vector2f{ 320.0, 240.0 } };

	while (window.isOpen()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			Character.move(sf::Vector2f{ -acceleration, 0 });
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			Character.move(sf::Vector2f{ acceleration, 0 });
		}
		else Character.Set_Frame(6, 2);

		sf::Event event;
		if( window.pollEvent(event) ){
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		else{
		
		window.clear();
		Character.ineract(Vector2f_from_Vector2i( sf::Mouse::getPosition( window )));
		Character.draw(window);
		window.display();
		sf::sleep(sf::milliseconds(20));
		}
	}

	std::cout << "Terminating application\n";
	return 0;
}

