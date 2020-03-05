#include "Level.h"
#include <cmath>

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;
	ball1 = new Ball(&windowSize);
	ball2 = new Ball(&windowSize);
	goomba = new Goomba(&windowSize);
	goomba2 = new Goomba(&windowSize);

	// initialise game objects
	ballT.loadFromFile("gfx/Beach_Ball.png");
	ball1->setSize(sf::Vector2f(100, 100));
	ball1->setOriginOffset(ball1->getSize().x / 2, ball1->getSize().y / 2);
	ball1->setBoundCircleRadius(ball1->getSize().x /2);
	ball1->setPosition(300, 230);
	ball1->setTexture(&ballT);
	ball1->setVelocity(-150, 0);

	ball2->setSize(sf::Vector2f(100, 100));
	ball2->setOriginOffset(ball1->getSize().x / 2, ball1->getSize().y / 2);
	ball2->setBoundCircleRadius(ball1->getSize().x / 2);
	ball2->setPosition(50, 200);
	ball2->setTexture(&ballT);
	ball2->setVelocity(150, 0);

	goombaT.loadFromFile("gfx/Goomba.png");
	goomba->setSize(sf::Vector2f(100, 100));
	goomba->setPosition(50, 350);
	goomba->setCollisionBox(25, 0, 50, 100);
	goomba->setTexture(&goombaT);
	goomba->setVelocity(150, 0);

	goomba2->setSize(sf::Vector2f(100, 100));
	goomba2->setPosition(200, 350);
	goomba2->setCollisionBox(25, 0, 50, 100);
	goomba2->setTexture(&goombaT);
	goomba2->setVelocity(-150, 0);
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{

}

// Update game objects
void Level::update(float dt)
{
	windowSize = window->getSize();

	if (circularCollisionCheck(ball1, ball2)) {
		ball1->collisionResponse(NULL);
		ball2->collisionResponse(NULL);
	}
	if (Collision::checkBoundingBox(goomba, goomba2)) {
		goomba->collisionResponse(NULL);
		goomba2->collisionResponse(NULL);
	}
	ball1->update(dt);
	ball2->update(dt);
	goomba->update(dt);
	goomba2->update(dt);
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(*ball1);
	window->draw(*ball2);
	window->draw(*goomba);
	window->draw(*goomba2);
	endDraw();
}

bool Level::circularCollisionCheck(Ball* b1, Ball* b2)
{
	float X1 = b1->getPosition().x + b1->getOriginOffset().x;
	float Y1 = b1->getPosition().y + b1->getOriginOffset().y;
	float X2 = b2->getPosition().x + b2->getOriginOffset().x;
	float Y2 = b2->getPosition().y + b2->getOriginOffset().y;

	if (pow(X2-X1,2) + pow(Y2-Y1,2) < pow(b2->getBoundCircleRadius()+b1->getBoundCircleRadius(),2)) 
	{
		return true;
	}
	return false;
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 100, 100));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}