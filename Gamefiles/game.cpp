#include "game.hpp"

void game::gameLoop(){
	gameObjectFactory.factorMainCharacter();
	bool state1 = true;
	clockPrevious = clock();

	//twee tests voor het frames bijhouden
	int secondsPassed = 0;
	int framecounter = 0;


    while (gameWindow.isOpen()) {
		clockNow = clock();
		auto elapsedTime = clockNow - clockPrevious;
		clockPrevious = clockNow;
		lag += elapsedTime;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
			if(state1){
				state1 = !state1;
				gameObjectFactory.factorNewGameState("gameState2.txt");
			}else{
				state1 = !state1;
				gameObjectFactory.factorNewGameState("gameState1.txt");
			}
		}
		
		framecounter++;
		if(framecounter == 60){
			framecounter = 0;
			secondsPassed++;
			std::cout<<secondsPassed<<std::endl;
		}



		std::unique_ptr<command> newCommand;
		newCommand  = gameInputHandler.handleInput();
		if(newCommand != NULL){
			newCommand->execute();
		}

		while(lag >= MS_PER_FRAME){
			gameObjectRenderer.update();
			lag -= MS_PER_FRAME;
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