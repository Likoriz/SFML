#pragma once
#include "Entity.h"
class WalkingEnemy : public Entity
{
private:
	void follow();
	void leave();
	void attack();
	void destruct();
	void move();
};

