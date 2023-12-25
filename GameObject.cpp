#include "GameObject.h"
using namespace std;

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

void GameObject::update()
{
	move();
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
