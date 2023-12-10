#pragma once
#include "Level.h"
#include "Audio.h"
#include "GameObject.h"
#include "Message.h"
#include <list>
#include <vector>


class Manager
{
private:
	
	Level* lvl;
	//Audio* audio;
	std::list<GameObject*> game;
	std::list<Message> queueOfMessages;

public:
	std::vector<MyDrawable> getDrawables();
	std::vector<Object> getObjects();
	void addObject(MyDrawable* object);
	void sendMSGAll();
	void updateAll();
	void startGame();
	void endGame();
};


