#include "game.hpp"

void game::gameLoop(){
	using namespace std::chrono;
	// bool state1 = true;
	uint64_t clockPrevious;
	int secondsPassed = 0;
	int framecounter = 0;
	clockPrevious = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    while (gameWindow.isOpen()) {
		loopTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - clockPrevious;

		while( loopTime < MS_PER_FRAME ){
			loopTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - clockPrevious;
		}
		clockPrevious = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

		// if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
		// 	if(state1){
		// 		state1 = !state1;
		// 		gameObjectFactory.factorNewGameState("gameState2.txt");
		// 	}else{
		// 		state1 = !state1;
		// 		gameObjectFactory.factorNewGameState("gameState1.txt");
		// 	}
		// }
		std::cout << "Test5" << std::endl;

		std::unique_ptr<command> newCommand;
		newCommand  = gameInputHandler.handleInput();
		if(newCommand != NULL){
			newCommand->execute();
		}
		std::cout << "Test6" << std::endl;

		gameObjectRenderer.update();
		
		std::cout << "Test7" << std::endl;
		
		framecounter++;
		if(framecounter == 60){
			framecounter = 0;
			secondsPassed++;
			std::cout<<secondsPassed<<std::endl;
		}
		std::cout << "Test8" << std::endl;

        gameWindow.clear();
        gameObjectRenderer.draw();
		gameWindow.display();

		std::cout << "Test9" << std::endl;

        sf::Event event;		
	    while( gameWindow.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){ 
				gameWindow.close();
			}
		}
	}
}