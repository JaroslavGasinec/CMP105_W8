#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/Collision.h"
#include <string>
#include <iostream>
#include "PlayBall.h"
#include "PlayerPad.h"
#include "Goomba.h"



class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();
	bool circularCollisionCheck(Ball* b1,Ball* b2);
	bool circularAABBCollisionCheck(Ball* b1, GameObject* o);

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	Ball* ball1;
	Ball* ball2;
	Ball* ball3;
	sf::Texture ballT;
	sf::Texture goombaT;
	GameObject* goomba;
	GameObject* goomba2;
	GameObject* player1;
	GameObject* player2;
	sf::Vector2u windowSize;
	
	sf::CircleShape check;

};