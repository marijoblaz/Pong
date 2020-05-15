#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Score
{
private:

	sf::Font font;
	sf::Text scoreText;

	sf::RectangleShape dashedLine;
	std::vector<sf::RectangleShape> dashedLines;

private:
	void initFont();
	void initScore(float posX, float posY);
	void initDashedLines(sf::Window& mWindow);
public:
	//core
	Score(sf::Window& mWindow, float posX, float posY);
	~Score();

	void setScore(int score);
	void render(sf::RenderTarget& mTarget);
};

