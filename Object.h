#pragma once
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include <string>
class Object
{
private:
	b2BodyDef bodyDef;
	b2Body* body;
	b2PolygonShape shape;
	b2FixtureDef fixtureDef;
	int speedY;
	int speedX;
	bool isJumpable;
public:
	Object(std::string name, sf::Rect<int> rect);
	Object();
	~Object();
	int getSpeed();
	void setSpeed();
	bool getJumpable();
	b2Body* getBody();
};

