#include "Manager.h"
#include "GameObject.h"
#include <vector>
#include"Player.h"
#include"WalkingEnemy.h"
#include "PlatformUsual.h"
#include "Box.h"
#include "Arrow.h"
#include <iostream>
using namespace std;
using namespace std::chrono;

Manager* Manager::instance = nullptr;

enum namesOfObjects {player, death, skill, slide, box, block, fall, disappear, walking, hiding, coin, arrow};


Manager::~Manager()
{
	for (auto x : game)
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
	GameObject* newObject;
	if(object->getName()=="player")
		newObject = new Player();
	if(object->getName()=="walking")
		newObject=new WalkingEnemy();
	if(object->getName()=="death"||object->getName()=="block"||object->getName()=="skill"||object->getName()=="slide"||object->getName()=="fall"||object->getName()=="disappear")
		newObject=new PlatformUsual();
	if(object->getName()=="box")
		newObject=new Box();
	if(object->getName()=="arrow")
		newObject=new Arrow();
	else
		newObject=new PlatformUsual();
	newObject->setDrawable(object);
	newObject->setObject(new Object(object->getName(), object->getRect()));
	game.push_back(newObject);
}

void Manager::sendMSGAll()
{
	for(auto msg:queueOfMessages)
		msg.target->sendMessage(msg);
	
}

void Manager::SendMessage(Message m)
{
	queueOfMessages.push_back(m);
}

void Manager::updateAll(float dt)
{
	/*for(auto obj:game)
		obj.*/

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

std::vector<GameObject*> Manager::getVectorByName(std::string name)
{
	std::vector<GameObject*> gameObjects=Manager::getInstance()->getGame();
	std::vector<GameObject*> vectToReturn;
	for(auto x:gameObjects)
	{
		if(x->getDrawable()->getName()==name)
			vectToReturn.push_back(x);
	}
	return vectToReturn;
}

bool Manager::getPause()
{
	return pause;
}

void Manager::setPause(bool state)
{
	pause = state;
}