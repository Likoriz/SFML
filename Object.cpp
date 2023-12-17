#include "Object.h"

Object::Object(std::string name, sf::Rect<int> rect)
{
	//b2BodyDef bodyDef;
	//bodyDef.type=b2_staticBody;
	//bodyDef.position.Set(rect.left+tileSize.x/2*(rect.width/tileSize.x-1),
}

Object::Object()
{

}

Object::~Object()
{
}

int Object::getSpeed()
{
	return 0;
}

void Object::setSpeed()
{
}

bool Object::getJumpable()
{
	return false;
}
