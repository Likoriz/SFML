#pragma once
#include "Entity.h"
class WalkingEnemy : public Entity
{
public:
	WalkingEnemy();
	void follow();
	void leave();
	void attack();
	void destruct();
	void sendMessage(Message m);
};

