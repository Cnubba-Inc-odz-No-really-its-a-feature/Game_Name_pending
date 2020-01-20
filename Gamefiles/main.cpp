#include "game.hpp"
#include "objectStorage.hpp"
#include "factory.hpp"


int main(){
    
<<<<<<< HEAD

    char state;
	std::cout<<"Do you want to work on the cardgame(C) or on the dungeon(D)?:\t";
	std::cin>>state;	


    sf::RenderWindow gameWindow{ sf::VideoMode{ 1920, 1080}, "SFML window"};
    game mainGame(gameWindow, state);
=======
    sf::RenderWindow gameWindow{ sf::VideoMode{ 1920, 1080}, "SFML window", 8};
    game mainGame(gameWindow);
>>>>>>> c35735399d3d02af40b33edab0c3aee27c611e87
    mainGame.gameLoop();
    return 0;

}