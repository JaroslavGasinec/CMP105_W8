#pragma once
#include "Framework/GameObject.h"
class Ball :
	public GameObject
{
protected:
	float boundCircleRadius = 20;
	sf::Vector2u originOffset;
	sf::Vector2u* windowSize;
	bool collisionActive = true;

public:
	Ball();
	Ball(sf::Vector2u* windowSize);
	~Ball();

	virtual void update(float dt) override;
	virtual void collisionResponse(GameObject* collider) override;
	void setOriginOffset(int x,int y);
	void setBoundCircleRadius(float r);
	float getBoundCircleRadius();
	sf::Vector2u getOriginOffset();
};

