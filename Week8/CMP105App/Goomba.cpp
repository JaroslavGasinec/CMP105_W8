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
	if (getPosition().x + getSize().x > windowSize->x || getPosition().x < 0) {
		velocity.x *= -1;
	}
	setPosition(getPosition() + velocity * dt);
}

void Goomba::collisionResponse(GameObject* collider)
{
	velocity.x *= -1;
}
