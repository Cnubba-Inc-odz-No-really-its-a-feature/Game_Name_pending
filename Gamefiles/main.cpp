#include "game.hpp"
#include "objectStorage.hpp"
#include "factory.hpp"


int main(){

    char state;
	std::cout<<"Do you want to work on the cardgame(C) or on the dungeon(D)?:\t";
	std::cin>>state;	


    sf::RenderWindow gameWindow{ sf::VideoMode{ 1920, 1080}, "SFML window", 8};
    game mainGame(gameWindow, state);
    mainGame.gameLoop();
    return 0;

}