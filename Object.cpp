#include "Object.h"
#include "Manager.h"


using namespace std;
using namespace sf;

//Object::Object(string name, Rect<int> rect)
//{
//	Vector2i tileSize = Manager::getInstance()->getLevel()->getTileSize();
//	if (name == "block")
//	{
//		bodyDef.type = b2_staticBody;
//		bodyDef.position.Set(rect.left + tileSize.x / 2 * (rect.width / tileSize.x - 1), rect.top + tileSize.y / 2 * (rect.height / tileSize.y - 1));
//		body = Manager::getInstance()->getWorld()->CreateBody(&bodyDef);
//		shape.SetAsBox(rect.width / 2, rect.height / 2);
//		body->CreateFixture(&shape, 1.0f);
//	}
//	else
//		if (name == "usual" || name == "skill" || name == "disappear" || name == "slide" || name == "fall" || name == "death" || name == "coin")
//		{
//			bodyDef.type = b2_staticBody;
//			bodyDef.position.Set(rect.left + tileSize.x / 2 * (rect.width / tileSize.x - 1), rect.top + tileSize.y / 2 * (rect.height / tileSize.y - 1) - tileSize.y);
//			body = Manager::getInstance()->getWorld()->CreateBody(&bodyDef);
//			shape.SetAsBox(rect.width / 2, rect.height / 2);
//			body->CreateFixture(&shape, 1.0f);
//		}
//		else
//			if (name == "hiding" || name == "walking" || name == "box")
//			{
//				bodyDef.type = b2_dynamicBody;
//				bodyDef.position.Set(rect.left + tileSize.x / 2 * (rect.width / tileSize.x - 1), rect.top + tileSize.y / 2 * (rect.height / tileSize.y - 1));
//				bodyDef.fixedRotation = true;
//				body = Manager::getInstance()->getWorld()->CreateBody(&bodyDef);
//				shape.SetAsBox(rect.width / 2, rect.height / 2);
//				body->CreateFixture(&shape, 1.0f);
//			}
//			else
//				if (name == "player")
//				{
//					bodyDef.type = b2_dynamicBody;
//					bodyDef.position.Set(rect.left, rect.top - tileSize.y);
//					bodyDef.fixedRotation = true;
//					body = Manager::getInstance()->getWorld()->CreateBody(&bodyDef);
//					shape.SetAsBox(rect.width / 2, rect.height / 2);
//					fixtureDef.shape = &shape;
//					fixtureDef.density = 1.0f; fixtureDef.friction = 1.0f;
//					body->CreateFixture(&fixtureDef);
//				}
//}

Object::Object(b2BodyType bodyType, int _x, int _y, Rect<int> rect, bool rotation, float density, float friction)
{
	bodyDef.type=bodyType;
	bodyDef.position.Set(_x, _y);
	bodyDef.fixedRotation=rotation;
	this;
	body=Manager::getInstance()->getWorld()->CreateBody(&bodyDef);
	shape.SetAsBox(rect.width/2, rect.height/2);
	
	if(friction)//player only
	{
		fixtureDef.shape=&shape;
		fixtureDef.density=density; fixtureDef.friction=friction;
		body->CreateFixture(&fixtureDef);

		b2PolygonShape sensorSBottom, sensorSLeft, sensorSRight;

		sensorSBottom.SetAsBox(4, 1, b2Vec2(0, 8), 0);
		sensorSLeft.SetAsBox(1.0f, 4.0f, b2Vec2(-8.0f, 0.0f), 0);
		sensorSRight.SetAsBox(1.0f, 4.0f, b2Vec2(8.0f, 0.0f), 0);

		b2FixtureDef sensorFDBottom, sensorFDLeft, sensorFDRight;
		sensorFDBottom.shape = &sensorSBottom;
		sensorFDLeft.shape = &sensorSLeft;
		sensorFDRight.shape = &sensorSRight;
		
		sensorFDBottom.isSensor = true;
		sensorFDLeft.isSensor = true;
		sensorFDRight.isSensor = true;
		
		body->CreateFixture(&sensorFDBottom);
		body->CreateFixture(&sensorFDLeft);
		body->CreateFixture(&sensorFDRight);
	}
	else
		body->CreateFixture(&shape, 1.0f);
}

Object::~Object()
{
	Manager::getInstance()->getWorld()->DestroyBody(body);

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

b2Body* Object::getBody()
{
	return body;
}