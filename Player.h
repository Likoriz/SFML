#pragma once
#include "Entity.h"
class Player : public Entity
{
private:
	bool weaponType;
	Medal activeMedals[2];
	Medal* collectedMedals;
	int exp;
	Skills* tree;
	int state;
	b2FixtureDef fixtureDef;
public:
	void destruct();
	void attack();
	void move();
	void openSkills();
	void closeSkills();
	void openMedals();
	void closeMedals();
	void receiveMedal();
	void receiveSkill();
};

