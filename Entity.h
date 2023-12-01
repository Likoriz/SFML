#pragma once
#include "GameObject.h"
class Entity : public GameObject
{
private:
	int hp;
	int damage;
	int defense;
	bool isInvincible;
	int radius;
public:
	Entity(std::string name);
	virtual void destruct() = 0;
	bool checkRadius();
	virtual void attack() = 0;
	virtual void move() = 0;

};

