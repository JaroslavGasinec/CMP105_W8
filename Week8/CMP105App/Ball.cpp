#include "Ball.h"

Ball::Ball()
{
}

Ball::Ball(sf::Vector2u* windowSize)
{
	this->windowSize = windowSize;
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
	if (getPosition().x + getSize().x > windowSize->x || getPosition().x < 0) {
		velocity.x *= -1;
	}
	setPosition(getPosition()+ velocity*dt);
}

void Ball::collisionResponse(GameObject* collider)
{
	velocity.x *= -1;
}

void Ball::setOriginOffset(int x, int y)
{
	originOffset.x = x;
	originOffset.y = y;
}

void Ball::setBoundCircleRadius(float r)
{
	boundCircleRadius = r;
}

float Ball::getBoundCircleRadius()
{
	return boundCircleRadius;
}

sf::Vector2u Ball::getOriginOffset()
{
	return originOffset;
}
