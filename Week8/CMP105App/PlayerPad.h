#pragma once
#include "Framework/GameObject.h"
class PlayerPad :
	public GameObject
{
	sf::Vector2u* windowSize;
	bool controlKeys = true;
	float speed = 250.0f;

public:
	PlayerPad(bool keys);
	PlayerPad(sf::Vector2u* windowSize, bool keys);
	~PlayerPad();

	void update(float dt) override;
	void handleInput(float dt) override;

};

