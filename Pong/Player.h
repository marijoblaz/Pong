#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>

class Player
{
public:
	Player(sf::Window& mWindow, bool left, bool CPU);
	~Player();

	//core
	void update(const float& dt);
	void render(sf::RenderTarget& mTarget);
	void updateCPUPlay(const float& dt, float ballPosX, float ballPosY);
public:
	//getters
	sf::FloatRect getGlobalPositionPlayer();
	sf::FloatRect getGlobalPositionPlayerUp();
	sf::FloatRect getGlobalPositionPlayerDown();

private:
	void move(bool moveUp, bool moveDown, const float& dt);
	void updateKeyPress(const float &dt);
	void initPlayer(bool side);

	//Helper funcs
	bool getPlayerPositionUp();
	bool getPlayerPositionDown();

private:

	sf::RectangleShape playerShape;
	sf::RectangleShape playerShapeUp;
	sf::RectangleShape playerShapeDown;

	float playerSpeed = 600.f;
	float windowX = 0;
	float windowY = 0;
	bool side = false;
	bool CPU = false;

};

