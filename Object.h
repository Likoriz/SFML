#pragma once
#include "box2d/box2d.h"
#include "box2d/b2_polygon_shape.h"
#include <string>
class Object
{
private:
	b2BodyDef bodyDef;
	b2Body* body;
	b2PolygonShape shape;
	int speedY;
	int speedX;
	bool isJumpable;
public:
	Object(std::string name);
	Object();
	~Object();
	int getSpeed();
	void setSpeed();
	bool getJumpable();
};

enum namesOfObjects {block, fall, dissaper, death};
