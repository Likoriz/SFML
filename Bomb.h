#pragma once
#include "Entity.h"
class Bomb : public Entity
{
public:
	void attack();
	void move();
	void destruct();
};

