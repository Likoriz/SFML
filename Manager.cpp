#include "Manager.h"
#include <vector>
using namespace std;
//std::vector<MyDrawable> getDrawables()
//{
//    return 0;
//}

Manager* Manager::instance=nullptr;

Manager::~Manager()
{
	for(auto x:game)
		delete x;
	for(auto x:queueOfMessages)
		delete x;
}

Manager* Manager::getInstance()
{
	if(!instance)
	{
		instance=new Manager();
	}
	return instance;
}

void Manager::Destroy()
{
	if(instance) delete instance;
}

//std::vector<MyDrawable*> Manager::getDrawables()
//{
//	vector<MyDrawable*> tmpObjects;
//	for(auto x:game)
//		tmpObjects.push_back(x.);
//	return tmpObjects;
//}

void Manager::addObject(MyDrawable* object)
{
	GameObject* newObject=new GameObject();
	newObject->setDrawable(object);
	game.push_back(newObject);
}

void Manager::sendMSGAll(Message* message)
{
}

void Manager::updateAll(float dt)
{
}

void Manager::startGame()
{
}

void Manager::endGame()
{
}

Level* Manager::getLevel()
{
	return lvl;
}
