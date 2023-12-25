#pragma once
#include "Level.h"
class GameObject;
#include "Audio.h"
#include "Message.h"
#include "box2d/box2d.h"
#include "box2d/b2_polygon_shape.h"
#include <list>
#include <vector>
#include <chrono>
#include <thread>

class Manager
{
private:
	b2World* world;
	static Manager* instance;
	Level* lvl;
	//Audio* audio;
	std::vector<GameObject*> game;
	std::list<Message> queueOfMessages;
	Manager();
	Manager(const Manager&);
	~Manager();
	bool pause;	
public:
	void setPause(bool state);
	bool getPause();
	static Manager* getInstance();
	static void Destroy();
	void addObject(MyDrawable* object);
	void sendMSGAll();
	void updateAll();
	void startGame();
	void endGame();
	std::vector<GameObject*> getGame();
	void SendMessage(Message m);
	b2World* getWorld();
	Level* getLevel();
	GameObject* getByFixture();
	GameObject* getByName(std::string name);
	std::vector<GameObject*> getVectorByName(std::string name);
	void handleOwnMessage(Message m);
};


