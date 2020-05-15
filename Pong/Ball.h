#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Ball
{
private:
	sf::RectangleShape ballShape;
	sf::Vector2f dir;

private:
	void moveBall(const float &dt);

public:
	Ball();
	~Ball();

	//Core
	void update(const float& dt);
	void render(sf::RenderTarget& mTarget);
public:
	//Getters
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getPosition();

	void setPosition(float x, float y);
	void setDirection(float dirX, float dirY);
};

