#pragma once
#include "Level.h"
class GameObject;
#include "Audio.h"
#include "Message.h"
#include <list>
#include <vector>


class Manager
{
private:
	static Manager* instance;
	Level* lvl;
	//Audio* audio;
	std::list<GameObject*> game;
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
	void getMessage();
	Level* getLevel();
};


