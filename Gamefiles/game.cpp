#include "game.hpp"
#include "card.hpp"


void game::gameLoop(){
	gameObjectFactory.factorMainCharacter();
	using namespace std::chrono;
	uint64_t clockPrevious;
	int secondsPassed = 0;
	int framecounter = 0;
	clockPrevious = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();




	std::vector<std::shared_ptr<std::vector<int>>> deckVector = gameObjectStorage.getDeckVector();


	deckClass testDeck(deckVector[0], deckVector[1], deckVector[2], deckVector[3]);
	
	auto testCard = testDeck.factorCard(1);






	std::cout << clockPrevious << std::endl;
	bool gamePlay = true;
	bool titlePlay = true;
	bool menuPlay = true;

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

		if(gameObjectStorage.keyActive == "Game" && gamePlay){
			buffer.loadFromFile("gameAssets/Sounds/game.wav");
			sound.setBuffer(buffer);
			sound.setLoop(true);
			sound.play();
			std::cout << "speelt dungeon game geluid" << std::endl;
			gamePlay = false;
			titlePlay = true;
			menuPlay = true;
		}else if(gameObjectStorage.keyActive == "Title" && titlePlay){
			buffer.loadFromFile("gameAssets/Sounds/game.wav");
			sound.setBuffer(buffer);
			sound.setLoop(true);
			sound.play();
			std::cout << "speelt title geluid" << std::endl;
			gamePlay = true;
			titlePlay = false;
			menuPlay = true;
		}else if(gameObjectStorage.keyActive == "Menu" && menuPlay){
			std::cout << "speelt menu geluid" << std::endl;
			gamePlay = true;
			titlePlay = true;
			menuPlay = false;
		}


        sf::Event event;		
	    while( gameWindow.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){ 
				gameWindow.close();
			}
		}
	}
}