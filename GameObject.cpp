#include "GameObject.h"
using namespace std;
//
//void GameObject::addDrawable(MyDrawable object_)
//{
//	drawables.push_back(object_);
//}
//
//void GameObject::addObject(Object object_)
//{
//	objects.push_back(object_);
//}
//
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
	object=sourceObject;
}

GameObject::GameObject()
{
	drawable=new MyDrawable();
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

