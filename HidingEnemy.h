#pragma once
#include "Entity.h"
class HidingEnemy : public Entity
{
private:
	void attack();
	void hide();
	void show();
	void destruct();
};

