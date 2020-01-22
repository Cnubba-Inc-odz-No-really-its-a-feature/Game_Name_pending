#include "game.hpp"
#include "card.hpp"


void game::gameLoop(){
	gameObjectFactory.factorMainCharacter();
	using namespace std::chrono;
	uint64_t clockPrevious;
	int secondsPassed = 0;
	int framecounter = 0;
	clockPrevious = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

	deckClass testDeck;
	auto testCard = testDeck.factorCard(1);






	std::cout << clockPrevious << std::endl;
    while (gameWindow.isOpen()) {
		loopTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - clockPrevious;

		while( loopTime < MS_PER_FRAME ){
			loopTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - clockPrevious;
		}
		clockPrevious = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

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
			std::cout<<secondsPassed<<std::endl;
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