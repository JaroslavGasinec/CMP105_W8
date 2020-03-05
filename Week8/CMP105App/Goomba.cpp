#include "Goomba.h"

Goomba::Goomba()
{
}

Goomba::Goomba(sf::Vector2u* windowSize)
{
	this->windowSize = windowSize;
}

Goomba::~Goomba()
{
}

void Goomba::update(float dt)
{
	if (getPosition().x + getSize().x + velocity.x * dt > windowSize->x || getPosition().x + velocity.x * dt < 0) {
		velocity.x *= -1;
	}
	setPosition(getPosition() + velocity * dt);
}

void Goomba::collisionResponse(GameObject* collider)
{
	if (collisionActive) {
		velocity.x *= -1;
		collisionActive = false;
		return;
	}
	collisionActive = true;
}
