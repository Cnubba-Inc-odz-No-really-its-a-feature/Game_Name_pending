#include "game.hpp"


void game::gameLoop(){
	using namespace std::chrono;
	// bool state1 = true;
	uint64_t clockPrevious;
	int secondsPassed = 0;
	int framecounter = 0;
	clockPrevious = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();



	// bool gamePlay = true;
	// bool titlePlay = true;
	// bool menuPlay = true;

    while (gameWindow.isOpen()) {
		loopTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - clockPrevious;

		while( loopTime < MS_PER_FRAME ){
			loopTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - clockPrevious;
		}
		clockPrevious = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();





		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			gameObjectStorage.storageDeck.newFight();
			std::cout<<"currentDecksize:" << gameObjectStorage.completeDeck.size()<<std::endl;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
			gameObjectStorage.storageDeck.newHand();
			std::cout<<"hand created of size: " << gameObjectStorage.cardsInHand.size() << std::endl;
		}






		std::unique_ptr<command> newCommand;
		newCommand  = gameInputHandler.handleInput();
		if(newCommand != NULL){
			newCommand->execute();
		}

		gameObjectRenderer.update();
		
		framecounter++;
		if(framecounter == 60){
			framecounter = 0;
			secondsPassed++;
		}

        gameWindow.clear();
        gameObjectRenderer.draw();


		gameWindow.display();


        sf::Event event;		
	    while( gameWindow.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){ 
				gameWindow.close();
			}
		}
	}
}