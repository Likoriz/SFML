#include "Manager.h"
#include "GameObject.h"
#include <vector>
#include"Player.h"
#include"WalkingEnemy.h"
#include "HidingEnemy.h"
#include "PlatformUsual.h"
#include "Box.h"
#include "Arrow.h"
#include <iostream>

using namespace std;
using namespace std::chrono;

Manager* Manager::instance = nullptr;

enum namesOfObjects { player, usual, death, skill, slide, box, block, fall, disappear, walking, hiding, coin, arrow };

Manager::~Manager()
{
	for (auto x : game)
		delete x;
}

Manager::Manager()
{
	lvl = new Level();
	pause = false;
	b2Vec2 gravity(0.0f, 200.0f);
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

void Manager::addObject(MyDrawable* object)
{
	GameObject* newObject;
	if (object->getName() == "player")
		newObject = new Player(object);
	else
		if (object->getName() == "walking")
			newObject = new WalkingEnemy(object);
		else
			if (object->getName() == "hiding")
				newObject = new HidingEnemy(object);
			else
				if (object->getName() == "death" || object->getName() == "block" || object->getName() == "usual" || object->getName() == "skill" || object->getName() == "slide" || object->getName() == "fall" || object->getName() == "disappear")
					newObject = new PlatformUsual(object);
				else
					if (object->getName() == "box")
						newObject = new Box(object);
					else
						if (object->getName() == "arrow")
							newObject = new Arrow(object);
						else
						{
							newObject = new PlatformUsual(object);
							//newObject->getObject()->getBody()->SetUserData((void*)"barrier");
						}
	
	game.push_back(newObject);
}

void Manager::sendMSGAll()
{
	for (auto msg : queueOfMessages)
		if (msg.target != nullptr)
			msg.target->sendMessage(msg);
		else
			handleOwnMessage(msg);
	queueOfMessages.clear();
}

void Manager::SendMessage(Message m)
{
	queueOfMessages.push_back(m);
}

void Manager::updateAll(duration<double> time_span, steady_clock::time_point& last_time, steady_clock::time_point current_time)
{
	for (auto x : game)
		if(x->getObject()->getBody()->GetType()==b2_dynamicBody)
			x->update(time_span, last_time, current_time);
}

void Manager::startGame()
{
}

void Manager::endGame()
{
}

std::vector<GameObject*>* Manager::getGame()
{
	return &game;
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
	std::vector<GameObject*>* gameObjects = Manager::getInstance()->getGame();
	for (auto x : *gameObjects)
	{
		if (x->getDrawable()->getName() == name)
			return x;
	}
}

std::vector<GameObject*> Manager::getVectorByName(std::string name)
{
	std::vector<GameObject*>* gameObjects = Manager::getInstance()->getGame();
	std::vector<GameObject*> vectToReturn;
	for (auto x : *gameObjects)
	{
		if (x->getDrawable()->getName() == name)
			vectToReturn.push_back(x);
	}
	return vectToReturn;
}

void Manager::handleOwnMessage(Message m)
{
	switch(m.type)
	{
	case Create:
		addObject(m.ctx.create.newObject);
		break;
	case Erase:
		if(m.ctx.erase.objectToDelete)
		{
			auto it=std::remove(game.begin(), game.end(), m.ctx.erase.objectToDelete);
			game.erase(it, game.end());
			delete m.ctx.erase.objectToDelete;
		}
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