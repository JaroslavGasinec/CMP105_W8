#include "PlayBall.h"

PlayBall::PlayBall()
{
}

PlayBall::PlayBall(sf::Vector2u* windowSize)
:Ball(windowSize)
{
}

PlayBall::~PlayBall()
{
}

void PlayBall::update(float dt)
{
	if (getPosition().x + getSize().x + velocity.x * dt > windowSize->x || getPosition().x + velocity.x*dt < 0) {
		setPosition(windowSize->x/2, windowSize->y/2);
	}
	if (getPosition().y + getSize().y + velocity.y * dt > windowSize->y || getPosition().y + velocity.y*dt < 0) {
		velocity.y *= -1;
	}
	setPosition(getPosition() + velocity * dt);
}

