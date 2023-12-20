#include "Manager.h"
#include "GameObject.h"
#include <vector>
#include <iostream>
using namespace std;
using namespace std::chrono;

Manager* Manager::instance = nullptr;

Manager::~Manager()
{
	for (auto x : game)
		delete x;
	for (auto x : queueOfMessages)
		delete x;
}

Manager::Manager()
{
	lvl = new Level();
	pause = false;
	b2Vec2 gravity(0.0f, 1.0f);
	world = new b2World(gravity);
}

Manager* Manager::getInstance()
{
	if (!instance)
	{
		instance = new Manager();
	}
	return instance;
}

void Manager::Destroy()
{
	if (instance) delete instance;
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
	GameObject* newObject = new GameObject();
	newObject->setDrawable(object);
	newObject->setObject(new Object(object->getName(), object->getRect()));
	game.push_back(newObject);
}

void Manager::sendMSGAll(Message* message)
{
}

void Manager::SendMessage(Message m)
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

std::vector<GameObject*> Manager::getGame()
{
	return game;
}

b2World* Manager::getWorld()
{
	return world;
}

Level* Manager::getLevel()
{
	return lvl;
}

GameObject* Manager::getByName(std::string name)
{
	std::vector<GameObject*> gameObjects = Manager::getInstance()->getGame();
	for (auto x : gameObjects)
	{
		if (x->getDrawable()->getName() == name)
			return x;
	}
}

bool Manager::getPause()
{
	return pause;
}

void Manager::setPause(bool state)
{
	pause = state;
}