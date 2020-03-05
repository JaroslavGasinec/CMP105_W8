#include "PlayerPad.h"

PlayerPad::PlayerPad(bool keys)
{
	controlKeys = keys;
}

PlayerPad::PlayerPad(sf::Vector2u* windowSize, bool keys)
{
	this->windowSize = windowSize;
	controlKeys = keys;
}

PlayerPad::~PlayerPad()
{
}

void PlayerPad::update(float dt)
{
	
}

void PlayerPad::handleInput(float dt)
{
	if (controlKeys) {
		if (input->isKeyDown(sf::Keyboard::W) && !(getPosition().y <= 0))
		{
			setPosition(getPosition().x, getPosition().y - speed * dt);
		}
		if (input->isKeyDown(sf::Keyboard::S) && !(getPosition().y + getSize().y >= windowSize->y))
		{
			setPosition(getPosition().x, getPosition().y + speed * dt);
		}
	}
	else {
		if (!(input->getMouseY() < getSize().y / 2) && !(input->getMouseY() > windowSize->y - getSize().y / 2)) {
			setPosition(getPosition().x,input->getMouseY()-getSize().y/2);
		}
	}
}
