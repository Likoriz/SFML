#pragma once
#include "Entity.h"
#include "Medal.h"
#include "Skills.h"

class Player : public Entity
{
private:
	bool weaponType;
	Medal* activeMedals;
	Medal* collectedMedals;
	int coins;
	Skills* tree;
	int state;
	b2FixtureDef fixtureDef;
public:
	void destruct();
	void attack();
	void move();
	void openMenu();
	void receiveMedal();
	void receiveSkill();
};

