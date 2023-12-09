#include "GameObject.h"

void GameObject::addDrawable(MyDrawable object_)
{
	drawables.push_back(object_);
}

void GameObject::addObject(Object object_)
{
	objects.push_back(object_);
}