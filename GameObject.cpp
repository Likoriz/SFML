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


