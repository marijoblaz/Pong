#include "Ball.h"

void Ball::moveBall(const float &dt)
{
	this->ballShape.move(this->dir * dt * 600.f);
}

Ball::Ball()
{
	this->ballShape.setSize(sf::Vector2f(20, 20));
	this->ballShape.setPosition(sf::Vector2f(500, 500));
	this->ballShape.setFillColor(sf::Color::White);
}

Ball::~Ball()
{

}

void Ball::update(const float& dt)
{
	this->moveBall(dt);
}

void Ball::render(sf::RenderTarget& mTarget)
{
	mTarget.draw(this->ballShape);
}

sf::FloatRect Ball::getGlobalBounds()
{
	return this->ballShape.getGlobalBounds();
}
sf::Vector2f Ball::getPosition()
{	
	return this->ballShape.getPosition();
}

void Ball::setPosition(float x, float y)
{
	this->ballShape.setPosition(x, y);
}

void Ball::setDirection(float dirX, float dirY)
{
	this->dir.x = dirX;
	this->dir.y = dirY;
}
