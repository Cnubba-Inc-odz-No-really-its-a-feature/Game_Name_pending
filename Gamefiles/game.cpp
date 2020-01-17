#include "game.hpp"
#include <SFML/Audio.hpp>
#include "background.hpp"

void game::gameLoop(){
	sf::SoundBuffer buffer;
	sf::Sound sound;
	if(!buffer.loadFromFile("Denzel Curry - Ultimate (Full Video).wav"));
	sound.setBuffer(buffer);
	//sound.pause();
	sound.play();
	//objectRenderer.factorObjects();
	auto defaultSize = sf::Vector2f((float)window.getSize().x, (float)window.getSize().y);
	auto lastSize = defaultSize;
	std::vector<std::string> files;
	files.push_back("background_back.png");
	files.push_back("background_front.png");
	files.push_back("background_middle.png");
	files.push_back("background_sky.png");
	std::shared_ptr<gameObject> bckgrnd(new background(files));
	storage.game->push_back(bckgrnd);
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