//#include "GameObject.h"
#include "Entity.h"

using namespace std;
using namespace std::chrono;

void GameObject::setDrawable(MyDrawable* object)
{
	drawable->setName(object->getName());
	drawable->setType(object->getType());
	drawable->setRect(object->getRect());
	drawable->setSprite(object->getSprite());
	drawable->setProperties(object->getProperties());

}

void GameObject::setObject(Object* sourceObject)
{
	object = sourceObject;
}

GameObject::GameObject()
{
	drawable = new MyDrawable();
}

void GameObject::update(duration<double> time_span, steady_clock::time_point& last_time, steady_clock::time_point current_time)
{
	move();
	Entity* object = (Entity*)this;
	object->checkCollision(time_span, last_time, current_time);
}

void GameObject::move()
{
	b2Vec2 pos = getObject()->getBody()->GetPosition();
	getDrawable()->getSprite()->setPosition(pos.x, pos.y);
}

GameObject::GameObject(const GameObject&)
{
}

GameObject::~GameObject()
{
	delete drawable;
	delete object;
}

MyDrawable* GameObject::getDrawable()
{
	return drawable;
}

Object* GameObject::getObject()
{
	return object;
}

bool GameObject::getIsOnGround()
{
	return isOnGround;
}

void GameObject::setIsOnGround(bool flag)
{
	isOnGround = flag;
}
