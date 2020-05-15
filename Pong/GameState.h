#pragma once
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Ball.h"
#include "Score.h"

class GameState
{
private:

	Ball* ball = nullptr;

	Player* player1 = nullptr;
	Player* player2 = nullptr;

	//Score
	int scoreP1 = 0;
	int scoreP2 = 0;
	Score* scorePlayer1 = nullptr;
	Score* scorePlayer2 = nullptr;


	//Ball direction
	sf::Vector2f ballDir;

	//Wall
	sf::RectangleShape wallTopShape;
	sf::RectangleShape wallBottomShape;

	//Sound
	sf::SoundBuffer bufferS1;
	sf::Sound soundS1;
	
	sf::SoundBuffer bufferS2;
	sf::Sound soundS2;

	//Bounds
	float windowX = 0;
	float windowY = 0;
	
	//Clock Look
	bool clockBool = false;
	int minutes;
	int hours;


	time_t now;
	tm* ltm;

private:

	void initPlayer(sf::Window& mWindow);
	void initSounds();
	void initBall();

	void updateBounds();
	void updateCollison();

public:
	GameState(sf::Window &mWindow);
	~GameState();

	void update(const float& dt);
	void render(sf::RenderTarget &mTarget);
};

