#include "game.hpp"
#include "card.hpp"


void game::gameLoop(){
	gameObjectFactory.factorMainCharacter();
	using namespace std::chrono;
	bool state1 = true;
	uint64_t clockPrevious = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	uint64_t clockNow;
	//twee tests voor het frames bijhouden
	int secondsPassed = 0;
	int framecounter = 0;

	deckClass testDeck;
	auto testCard = testDeck.factorCard(1);






	std::cout << clockPrevious << std::endl;
    while (gameWindow.isOpen()) {
		clockNow = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		auto elapsedTime = clockNow - clockPrevious;
		clockPrevious = clockNow;
		lag += elapsedTime;
		//std::cout << lag << std::endl;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
			if(state1){
				state1 = !state1;
				gameObjectFactory.factorNewGameState("gameState2.txt");
			}else{
				state1 = !state1;
				gameObjectFactory.factorNewGameState("gameState1.txt");
			}
		}
		



		std::unique_ptr<command> newCommand;
		newCommand  = gameInputHandler.handleInput();
		if(newCommand != NULL){
			newCommand->execute();
		}

		while(lag >= MS_PER_FRAME){
		framecounter++;
		if(framecounter == 60){
			framecounter = 0;
			secondsPassed++;
			std::cout<<secondsPassed<<std::endl;
		}
			gameObjectRenderer.update();
			lag -= MS_PER_FRAME;
		}
        gameWindow.clear();
        gameObjectRenderer.draw();


		testCard->draw(gameWindow);
		gameWindow.display();

        sf::Event event;		
	    while( gameWindow.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){ 
				gameWindow.close();
			}
		}
	}
}