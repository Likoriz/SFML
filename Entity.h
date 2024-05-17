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
	~Entity();
	virtual void destruct() = 0;
	virtual void attack(Message m) = 0;

	void setHP(int hp_);
	void setDMG(int dmg);
	void setDEF(int def);
	void setRadius(int rad);

	int getHP();
	int getDMG();
	int getDEF();
	int getRadius();

	void setInvicibility(bool flag);
	bool getInvincibility();

	virtual void checkCollision(std::chrono::duration<double> time_span, std::chrono::steady_clock::time_point& last_time, std::chrono::steady_clock::time_point current_time) = 0;
};

