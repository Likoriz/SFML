#pragma once
#include "Level.h"
#include "Audio.h"
#include "GameObject.h"
struct MessageQ
{
	int a;
};

class Manager
{
private:
	Level* lvl;
	//Audio* audio;
	GameObject** game;
	MessageQ* queueOfMessages;
public:
	void sendMSG();
	void update();
	void startGame();
	void endGame();
};

