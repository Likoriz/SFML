#pragma once
#include "Entity.h"
class HidingEnemy : public Entity
{
public:
	HidingEnemy();
	void sendMessage(Message m);
	void attack();
	void hide();
	void show();
	void destruct();
};

