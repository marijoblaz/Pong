#include "GameState.h"
#include <ctime>

#pragma warning(disable:4996)

void GameState::initPlayer(sf::Window& mWindow)
{
	this->player1 = new Player(mWindow, 1 ,1);
	this->player2 = new Player(mWindow, 0, 0);
}

void GameState::initSounds()
{
	if (!this->bufferS1.loadFromFile("Sounds/ping_pong_8bit_beeep.ogg")) {
		std::cout << "FAIL TO LOAD AUDIO\n";
	}
	this->soundS1.setBuffer(bufferS1);
	this->soundS1.setVolume(20);

	if (!this->bufferS2.loadFromFile("Sounds/ping_pong_8bit_plop.ogg")) {
		std::cout << "FAIL TO LOAD AUDIO\n";
	}
	this->soundS2.setBuffer(bufferS2);
	this->soundS2.setVolume(20);
}

void GameState::initBall()
{
	this->ball = new Ball();

	this->ballDir.x = 1.f;
	this->ballDir.y = 1.f;

	this->ball->setDirection(ballDir.x, ballDir.y);
}

void GameState::updateBounds()
{
	if (this->ball->getPosition().x < 90) {
		this->ballDir.x = 1.f;
		this->ballDir.y = 1.f;

		this->ball->setDirection(ballDir.x, ballDir.y);
		this->ball->setPosition(150.f, 300.f);

		//Set the score text
		this->hours = this->ltm->tm_hour;
		this->soundS2.play();
		this->scoreP2++;
		this->scorePlayer2->setScore(this->scoreP2);
		sf::sleep(sf::milliseconds(500));
	}
	if (this->ball->getPosition().x > this->windowX - 110) {
		this->ballDir.x = -1.f;
		this->ballDir.y = 1.f;

		this->ball->setDirection(ballDir.x, ballDir.y);
		this->ball->setPosition(this->windowX - 150.f, 300.f);

		//Set the score text
		this->minutes = this->ltm->tm_min;
		this->soundS2.play();
		this->scoreP1++;
		this->scorePlayer1->setScore(this->scoreP1);
		sf::sleep(sf::milliseconds(500));
	}

}

void GameState::updateCollison()
{
	//Player 2
	if (this->ball->getGlobalBounds().intersects(this->player2->getGlobalPositionPlayerUp())) {
		this->soundS1.play();

		this->ballDir.x = -ballDir.x;
		if(!ballDir.y < -1)
			this->ballDir.y = ballDir.y - 0.5f;

		this->ball->setDirection(ballDir.x, ballDir.y);
	}else if (this->ball->getGlobalBounds().intersects(this->player2->getGlobalPositionPlayerDown())) {
		this->soundS1.play();
		this->ballDir.x = -ballDir.x;
		if (!ballDir.y > 1)
			this->ballDir.y = ballDir.y + 0.5f;

		this->ball->setDirection(ballDir.x, ballDir.y);
	}else if (this->ball->getGlobalBounds().intersects(this->player2->getGlobalPositionPlayer())) {
		this->soundS1.play();
		this->ballDir.x = -ballDir.x;
		this->ballDir.y = ballDir.y;

		this->ball->setDirection(ballDir.x, ballDir.y);
	}



	//Player 1
	if (this->ball->getGlobalBounds().intersects(this->player1->getGlobalPositionPlayerUp())) {
		this->soundS1.play();
		this->ballDir.x = -ballDir.x;
		if (!ballDir.y < -1)
			this->ballDir.y = ballDir.y - 0.5f;

		this->ball->setDirection(ballDir.x, ballDir.y);
	}else if (this->ball->getGlobalBounds().intersects(this->player1->getGlobalPositionPlayerDown())) {
		this->soundS1.play();
		this->ballDir.x = -ballDir.x;
		if (!ballDir.y > 1)
			this->ballDir.y = ballDir.y + 0.5f;

		this->ball->setDirection(ballDir.x, ballDir.y);
	}
	else if (this->ball->getGlobalBounds().intersects(this->player1->getGlobalPositionPlayer())) {
		this->soundS1.play();
		this->ballDir.x = -ballDir.x;
		this->ballDir.y = ballDir.y;

		this->ball->setDirection(ballDir.x, ballDir.y);
	}


	//Walls
	if (this->ball->getGlobalBounds().intersects(this->wallBottomShape.getGlobalBounds())) {
		this->soundS1.play();
		this->ballDir.x = ballDir.x;
		this->ballDir.y = -ballDir.y;

		this->ball->setDirection(ballDir.x, ballDir.y);
	}
	if (this->ball->getGlobalBounds().intersects(this->wallTopShape.getGlobalBounds()))
	{
		this->soundS1.play();
		this->ballDir.x = ballDir.x;
		this->ballDir.y = -ballDir.y;

		this->ball->setDirection(ballDir.x, ballDir.y);
	}

}

GameState::GameState(sf::Window& mWindow)
{
	this->initPlayer(mWindow);
	this->initBall();
	this->initSounds();

	this->scorePlayer1 = new Score(mWindow ,mWindow.getSize().x / 2 - 330, 50.f);
	this->scorePlayer2 = new Score(mWindow , mWindow.getSize().x / 2 + 200, 50.f);

	this->scorePlayer1->setScore(this->scoreP1);
	this->scorePlayer2->setScore(this->scoreP2);

	this->windowX = (float)mWindow.getSize().x;
	this->windowY = (float)mWindow.getSize().y;

	this->wallBottomShape.setFillColor(sf::Color(100,100,100,255));
	this->wallBottomShape.setSize(sf::Vector2f(mWindow.getSize().x - 160, 30));
	this->wallBottomShape.setPosition(sf::Vector2f(80, mWindow.getSize().y - this->wallBottomShape.getGlobalBounds().height - 20));

	this->wallTopShape.setFillColor(sf::Color(100, 100, 100, 255));
	this->wallTopShape.setSize(sf::Vector2f(mWindow.getSize().x - 160, 30));
	this->wallTopShape.setPosition(sf::Vector2f(80, 20));

}

GameState::~GameState()
{
	delete this->player1;
	delete this->player2;

	delete this->scorePlayer1;
	delete this->scorePlayer2;

	delete this->ball;
}

void GameState::update(const float& dt)
{
	this->now = time(0);
	this->ltm = localtime(&now);

	this->player1->update(dt);
	this->player2->update(dt);
	this->ball->update(dt);

	this->updateCollison();
	this->updateBounds();

	if (this->clockBool) {

		if (this->hours != ltm->tm_hour)
			this->player1->updateCPUPlay(dt, this->ball->getPosition().x, this->windowY/2);
		else
			this->player1->updateCPUPlay(dt, this->ball->getPosition().x, this->ball->getPosition().y);

		if(this->minutes != ltm->tm_min)
			this->player2->updateCPUPlay(dt, this->ball->getPosition().x, this->windowY / 2);
		else
			this->player2->updateCPUPlay(dt, this->ball->getPosition().x, this->ball->getPosition().y);

		this->scorePlayer1->setScore(ltm->tm_hour);
		this->scorePlayer2->setScore(ltm->tm_min);
	}
	else
	{
		this->player1->updateCPUPlay(dt, this->ball->getPosition().x, this->ball->getPosition().y);
		this->player2->updateCPUPlay(dt, this->ball->getPosition().x, this->ball->getPosition().y);
	}

}

void GameState::render(sf::RenderTarget& mTarget)
{
	this->scorePlayer1->render(mTarget);
	this->scorePlayer2->render(mTarget);

	this->player1->render(mTarget);
	this->player2->render(mTarget);
	this->ball->render(mTarget);


	mTarget.draw(wallBottomShape);
	mTarget.draw(wallTopShape);
}
