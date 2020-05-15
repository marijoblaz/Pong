#include "Score.h"

void Score::initFont()
{
	this->font.loadFromFile("Font/pong.ttf");
}

void Score::initScore(float posX, float posY)
{
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(200);
	this->scoreText.setPosition(posX, posY);
}

void Score::initDashedLines(sf::Window& mWindow)
{
	this->dashedLine.setSize(sf::Vector2f(30.f, 100.f));
	this->dashedLine.setFillColor(sf::Color(100, 100, 100, 255));

	for (int i = 0; i < 6; i++)
	{
		this->dashedLines.push_back(dashedLine);
		this->dashedLines[0].setPosition(sf::Vector2f(mWindow.getSize().x / 2 - this->dashedLine.getGlobalBounds().width, 30));
		this->dashedLines[i].setPosition(sf::Vector2f(mWindow.getSize().x / 2 - this->dashedLine.getGlobalBounds().width, 190 * i));
	}
}

Score::Score(sf::Window& mWindow, float posX, float posY)
{
	this->initFont();
	this->initScore(posX, posY);
	this->initDashedLines(mWindow);
}

Score::~Score()
{
}

void Score::setScore(int score)
{
	this->scoreText.setString(std::to_string(score));
}

void Score::render(sf::RenderTarget& mTarget)
{
	mTarget.draw(this->scoreText);
	for (unsigned int i = 0; i < this->dashedLines.size(); i++)
	{
		mTarget.draw(this->dashedLines[i]);
	}
}
