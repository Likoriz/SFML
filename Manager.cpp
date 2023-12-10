#include "Manager.h"

//std::vector<MyDrawable> getDrawables()
//{
//    return 0;
//}

void Manager::addObject(MyDrawable* object)
{
	GameObject* newObject;
	newObject->setDrawable(object);
	game.push_back(newObject);
}
