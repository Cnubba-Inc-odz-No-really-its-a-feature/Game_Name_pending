#include "game.hpp"
#include <SFML/Audio.hpp>

void game::gameLoop(){
	using namespace std::chrono;
	// bool state1 = true;
	uint64_t clockPrevious;
	int secondsPassed = 0;
	int framecounter = 0;
	clockPrevious = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

	sf::Sound sound;
	sf::SoundBuffer buffer;

	bool gamePlay = true;
	bool menuPlay = true;
	bool battlePlay = true;

    while (gameWindow.isOpen()) {
		loopTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - clockPrevious;

		while( loopTime < MS_PER_FRAME ){
			loopTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - clockPrevious;
		}
		clockPrevious = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
			std::cout<<"drawing new hand" << std::endl;
			gameObjectStorage.cardHand.newHand();
			std::cout<<"hand created of size: " << gameObjectStorage.cardsInHand.size() << std::endl;
		}




		std::shared_ptr<command> newCommand;
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

        if(gameObjectStorage.keyActive.at(0) == 'r' && gamePlay){
			buffer.loadFromFile("gameAssets/Sounds/game.wav");
			sound.setBuffer(buffer);
			sound.setLoop(true);
			sound.play();
			sound.setVolume(100);
			gamePlay = false;
			battlePlay = true;
			menuPlay = true;
		}else if(gameObjectStorage.keyActive.at(0) == 'b' && battlePlay){
			buffer.loadFromFile("gameAssets/Sounds/battle.wav");
			sound.setBuffer(buffer);
			sound.setLoop(true);
			sound.play();
			sound.setVolume(20);
			gamePlay = true;
			battlePlay = false;
			menuPlay = true;
		}else if(gameObjectStorage.keyActive.at(0) == 'm' && menuPlay){
			std::cout << "speelt menu.wav" << std::endl;
			buffer.loadFromFile("gameAssets/Sounds/menu.wav");
			sound.setBuffer(buffer);
			sound.setLoop(true);
			sound.play();
			sound.setVolume(20);
			gamePlay = true;
			battlePlay = true;
			menuPlay = false;			
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