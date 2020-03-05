#pragma once
#include "Ball.h"
class PlayBall :
	public Ball
{
public:
	PlayBall();
	PlayBall(sf::Vector2u* windowSize);
	~PlayBall();

	void update(float dt) override;
};

