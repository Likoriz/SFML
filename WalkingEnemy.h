#pragma once
#include "Entity.h"
class WalkingEnemy : public Entity
{
public:
	void follow();
	void leave();
	void attack();
	void destruct();
	void move();
	void sendMessage(Message m);
};

