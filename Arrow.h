#pragma once
#include "Entity.h"
class Arrow : public Entity
{
public:
	void attack();
	void move();
	void destruct();
	void sendMessage(Message m);
};


