#pragma once
#include "Entity.h"
class HidingEnemy : public Entity
{
private:
	int health;
	bool isDead;
public:
	HidingEnemy(MyDrawable* object);
	void sendMessage(Message m);
	void attack();
	void hide();
	void show();
	void destruct();
	void checkCollision(std::chrono::duration<double> time_span, std::chrono::steady_clock::time_point& last_time, std::chrono::steady_clock::time_point current_time);
};

