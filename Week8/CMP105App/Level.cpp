#include "Level.h"
#include <cmath>
#include "Framework/Vector.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;
	windowSize = window->getSize();
	ball1 = new Ball(&windowSize);
	ball2 = new Ball(&windowSize);
	ball3 = new PlayBall(&windowSize);
	goomba = new Goomba(&windowSize);
	goomba2 = new Goomba(&windowSize);
	player1 = new PlayerPad(&windowSize, true);
	player2 = new PlayerPad(&windowSize, false);

	// initialise game objects

	ballT.loadFromFile("gfx/Beach_Ball.png");
	ball1->setSize(sf::Vector2f(25, 25));
	ball1->setOriginOffset(ball1->getSize().x / 2, ball1->getSize().y / 2);
	ball1->setBoundCircleRadius(ball1->getSize().x /2);
	ball1->setPosition(300, 20);
	ball1->setTexture(&ballT);
	ball1->setVelocity(-150, 0);

	ball2->setSize(sf::Vector2f(25, 25));
	ball2->setOriginOffset(ball1->getSize().x / 2, ball1->getSize().y / 2);
	ball2->setBoundCircleRadius(ball2->getSize().x / 2);
	ball2->setPosition(50, 30);
	ball2->setTexture(&ballT);
	ball2->setVelocity(150, 0);

	ball3->setSize(sf::Vector2f(100, 100));
	ball3->setOriginOffset(ball3->getSize().x / 2, ball3->getSize().y / 2);
	ball3->setBoundCircleRadius(ball3->getSize().x / 2);
	ball3->setPosition(windowSize.x / 2, windowSize.y / 2);
	ball3->setTexture(&ballT);
	ball3->setVelocity(150,150);

	goombaT.loadFromFile("gfx/Goomba.png");
	goomba->setSize(sf::Vector2f(25, 25));
	goomba->setPosition(50, 40);
	goomba->setCollisionBox(goomba->getSize().x/4, 0, goomba->getSize().x / 2, goomba->getSize().y);
	goomba->setTexture(&goombaT);
	goomba->setVelocity(150, 0);

	goomba2->setSize(sf::Vector2f(25, 25));
	goomba2->setPosition(200, 40);
	goomba2->setCollisionBox(goomba2->getSize().x / 4, 0, goomba2->getSize().x / 2, goomba2->getSize().y);
	goomba2->setTexture(&goombaT);
	goomba2->setVelocity(-150, 0);

	player1->setSize(sf::Vector2f(20,100));
	player1->setPosition(windowSize.x-windowSize.x/6, windowSize.y/2);
	player1->setFillColor(sf::Color::Red);
	player1->setCollisionBox(0, 0, player1->getSize().x, player1->getSize().y);
	player1->setInput(input);
	
	player2->setSize(sf::Vector2f(20, 100));
	player2->setPosition(windowSize.x / 6, windowSize.y / 2);
	player2->setFillColor(sf::Color::Red);
	player2->setCollisionBox(0, 0, player1->getSize().x, player1->getSize().y);
	player2->setInput(input);

	check.setRadius(10);
	check.setFillColor(sf::Color::Green);
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	player1->handleInput(dt);
	player2->handleInput(dt);

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
	if (circularAABBCollisionCheck(ball3, player1) || circularAABBCollisionCheck(ball3, player2)) {
		ball3->collisionResponse(NULL);
	}

	ball1->update(dt);
	ball2->update(dt);
	ball3->update(dt);
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
	window->draw(*player1);
	window->draw(*player2);
	window->draw(*ball3);
	window->draw(check);
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

bool Level::circularAABBCollisionCheck(Ball* b, GameObject* o)
{
	float BX = b->getPosition().x + b->getOriginOffset().x;
	float BY = b->getPosition().y + b->getOriginOffset().y;
	float OX = o->getPosition().x;
	float OY = o->getPosition().y;
	sf::Vector2i point;

	if (BX > OX && BX < OX + o->getSize().x) {
		if (BY < OY) {
			point = sf::Vector2i(BX,BY + b->getBoundCircleRadius());
		}
		else { point = sf::Vector2i(BX, BY - b->getBoundCircleRadius()); }
	}

	else if (BY > OY && BY < OY + o->getSize().y) {
		if (BX < OX) {
			point = sf::Vector2i(BX + b->getBoundCircleRadius(), BY);
		}
		else { point = sf::Vector2i(BX - b->getBoundCircleRadius(), BY); }
	}

	else {
		if (BX > OX) { OX += o->getSize().x; }
		if (BY > OY) { OY += o->getSize().y; }

		sf::Vector2f calculated = sf::Vector2f(OX - BX, OY - BY);
		calculated /= Vector::magnitude(calculated);
		calculated *= b->getBoundCircleRadius();
		calculated += sf::Vector2f(BX, BY);
		point = sf::Vector2i(calculated.x, calculated.y);
	}

	//check.setPosition(point.x,point.y);
	return Collision::checkBoundingBox(o, point);
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