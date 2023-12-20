#pragma once
#include "Level.h"
class GameObject;
#include "Audio.h"
#include "Message.h"
#include "box2d/box2d.h"
#include "box2d/b2_polygon_shape.h"
#include <list>
#include <vector>


class Manager
{
private:
	b2World* world;
	static Manager* instance;
	Level* lvl;
	//Audio* audio;
	std::vector<GameObject*> game;
	std::list<Message*> queueOfMessages;
	Manager();
	Manager(const Manager&);
	~Manager();
	bool pause;
	
public:
	void setPause(bool state);
	bool getPause();
	static Manager* getInstance();
	static void Destroy();
	//std::vector<MyDrawable> getDrawables();
	//std::vector<Object> getObjects();
	void addObject(MyDrawable* object);
	void sendMSGAll(Message* message);
	void updateAll(float dt);
	void startGame();
	void endGame();
	std::vector<GameObject*> getGame();
	void SendMessage(Message m);
	b2World* getWorld();
	Level* getLevel();
	GameObject* getByName(std::string name);
};


