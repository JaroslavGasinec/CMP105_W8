#pragma once
#include "Framework/GameObject.h"
class Goomba :
	public GameObject
{
	sf::Vector2u* windowSize;
	bool collisionActive = true;

public:
	Goomba();
	Goomba(sf::Vector2u* windowSize);
	~Goomba();

	void update(float dt) override;
	void collisionResponse(GameObject* collider) override;

};

