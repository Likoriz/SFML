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
	Entity() {};
	virtual void destruct() = 0;
	bool checkRadius();
	virtual void attack() = 0;
	

	void setHP(int hp_);
	void setDMG(int dmg);
	void setDEF(int def);
	void setRadius(int rad);

	int getHP();
	int getDMG();
	int getDEF();
	int getRadius();
};

