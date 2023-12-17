#include "Object.h"
#include "Manager.h"


using namespace std;
using namespace sf;

Object::Object(string name, Rect<int> rect)
{
	Vector2i tileSize=Manager::getInstance()->getLevel()->getTileSize();
	if(name=="block" || name=="skill" || name=="disappear" || name=="slide" || name=="fall" || name=="death")
	{
		bodyDef.type=b2_staticBody;
		bodyDef.position.Set(rect.left+tileSize.x/2*(rect.width/tileSize.x-1),
			rect.top+tileSize.y/2*(rect.height/tileSize.y-1));
		body=Manager::getInstance()->getWorld()->CreateBody(&bodyDef);
		shape.SetAsBox(rect.width/2, rect.height/2);
		body->CreateFixture(&shape, 1.0f);
	}
	else if(name=="coin")
	{
		bodyDef.type=b2_dynamicBody;
		bodyDef.position.Set(rect.left+tileSize.x/2*(rect.width/tileSize.x-1),
			rect.top+tileSize.y/2*(rect.height/tileSize.y-1));
		bodyDef.fixedRotation=true;
		body=Manager::getInstance()->getWorld()->CreateBody(&bodyDef);
		shape.SetAsBox(rect.width/2, rect.height/2);
		body->CreateFixture(&shape, 1.0f);
	}
	else if(name=="hiding" || name=="walking")
	{
		bodyDef.type=b2_dynamicBody;
		bodyDef.position.Set(rect.left+
			tileSize.x/2*(rect.width/tileSize.x-1),
			rect.top+tileSize.y/2*(rect.height/tileSize.y-1));
		bodyDef.fixedRotation=true;
		body=Manager::getInstance()->getWorld()->CreateBody(&bodyDef);
		shape.SetAsBox(rect.width/2, rect.height/2);
		body->CreateFixture(&shape, 1.0f);
	}
	else if(name=="player")
	{
		bodyDef.type=b2_dynamicBody;
		bodyDef.position.Set(rect.left, rect.top);
		bodyDef.fixedRotation=true;
		body=Manager::getInstance()->getWorld()->CreateBody(&bodyDef);
		shape.SetAsBox(rect.width/2, rect.height/2);
		fixtureDef.shape=&shape;
		fixtureDef.density=1.0f; fixtureDef.friction=0.3f;
	}

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
