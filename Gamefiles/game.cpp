#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

game::game(sf::RenderWindow& window):
    window(window),
    objectRenderer(window, storage),
    gameInputHandler(storage),
    objectFactory(storage, window)
{
    objectFactory.factorObjectsFromFile("objects.txt");
    std::cout<<(*storage.game).size()<<std::endl;
}

void game::gameLoop(){
	sf::Music music;
	if(!music.openFromFile("Denzel Curry - Ultimate (Full Video).wav"))
	music.play();
	music.pause();
	music.play();
	music.setVolume(20.0);
	//objectRenderer.factorObjects();
    while (window.isOpen()) {
		time(&timerCurrent);
		auto elapsed = timerCurrent - timerPrevious;
		timerPrevious = timerCurrent;
		lag += elapsed;		

		command* newCommand;
		newCommand  = gameInputHandler.handleInput();
		if(newCommand != NULL){
			newCommand->execute();
		}
		delete newCommand;

		while(lag >= MS_PER_FRAME){

			lag -= MS_PER_FRAME;
		}


        window.clear();
        objectRenderer.update();
        objectRenderer.draw();
		window.display();

        sf::Event event;		
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}else if(event.type == sf::Event::Resized){
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        		window.setView(sf::View(visibleArea));
			}
		}
       
	}
}