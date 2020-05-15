#include "Player.h"

void Player::update(const float& dt)
{
	//std::cout << "Player updating" << std::endl;
	
	if(!CPU)
		this->updateKeyPress(dt);

	this->playerShapeUp.setPosition(this->playerShape.getPosition());
	this->playerShapeDown.setPosition(this->playerShape.getPosition().x, this->playerShape.getPosition().y + this->playerShape.getGlobalBounds().height - this->playerShapeDown.getGlobalBounds().height);

}

void Player::render(sf::RenderTarget& mTarget)
{
	mTarget.draw(this->playerShape);
}

sf::FloatRect Player::getGlobalPositionPlayerUp()
{
	return this->playerShapeUp.getGlobalBounds();
}

sf::FloatRect Player::getGlobalPositionPlayerDown()
{
	return this->playerShapeDown.getGlobalBounds();
}

Player::Player(sf::Window& mWindow, bool side, bool CPU)
{

	this->windowX = (float)mWindow.getSize().x;
	this->windowY = (float)mWindow.getSize().y;

	this->side = side;
	this->CPU = CPU;

	this->initPlayer(side);
}

Player::~Player()
{
}

sf::FloatRect Player::getGlobalPositionPlayer()
{
	return this->playerShape.getGlobalBounds();
}

void Player::move(bool moveUp, bool moveDown, const float& dt)
{
	if(moveUp && this->getPlayerPositionUp())
		this->playerShape.move(sf::Vector2f(0, -1) * dt * this->playerSpeed);
	if(moveDown && this->getPlayerPositionDown())
		this->playerShape.move(sf::Vector2f(0, 1) * dt * this->playerSpeed);
}

void Player::updateKeyPress(const float &dt)
{
	if (this->side) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			this->move(1, 0, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			this->move(0, 1, dt);
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			this->move(1, 0, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			this->move(0, 1, dt);
		}	
	}

}

void Player::updateCPUPlay(const float& dt, float ballPosX, float ballPosY)
{
	if (CPU) {
		if (side) {
			if (this->playerShape.getPosition().y + this->playerShape.getGlobalBounds().height / 2 > ballPosY + 70
				&& this->getPlayerPositionUp() 
				&& ballPosX < this->windowX / 2) 
			{
				this->playerShape.move(sf::Vector2f(0, -1) * dt * this->playerSpeed);
			}
			else if (this->playerShape.getPosition().y + this->playerShape.getGlobalBounds().height / 2 < ballPosY - 70
				&& this->getPlayerPositionDown() 
				&& ballPosX < this->windowX / 2) 
			{
				this->playerShape.move(sf::Vector2f(0, 1) * dt * this->playerSpeed);
			}
		}
		else {
			if (this->playerShape.getPosition().y + this->playerShape.getGlobalBounds().height / 2 > ballPosY + 70
				&& this->getPlayerPositionUp()
				&& ballPosX > this->windowX / 2)
			{
				this->playerShape.move(sf::Vector2f(0, -1) * dt * this->playerSpeed);
			}
			else if (this->playerShape.getPosition().y + this->playerShape.getGlobalBounds().height / 2 < ballPosY - 70
				&& this->getPlayerPositionDown()
				&& ballPosX > this->windowX / 2)
			{
				this->playerShape.move(sf::Vector2f(0, 1) * dt * this->playerSpeed);
			}
		}
	}
}

void Player::initPlayer(bool side)
{
	this->playerShape.setFillColor(sf::Color::White);
	this->playerShape.setSize(sf::Vector2f(20, 150));

	this->playerShapeUp.setSize(sf::Vector2f(this->playerShape.getGlobalBounds().width, this->playerShape.getGlobalBounds().height/4));
	this->playerShapeDown.setSize(sf::Vector2f(this->playerShape.getGlobalBounds().width, this->playerShape.getGlobalBounds().height/4));

	if (side)
		this->playerShape.setPosition(80.f, this->windowY/2);
	else
		this->playerShape.setPosition(this->windowX - 100.f, this->windowY / 2);
		

}

bool Player::getPlayerPositionUp()
{
	if (this->playerShape.getPosition().y < 50)
		return false;
	else
		return true;
}

bool Player::getPlayerPositionDown()
{
	if (this->playerShape.getPosition().y + this->playerShape.getGlobalBounds().height > this->windowY - 50)
		return false;
	else
		return true;
}