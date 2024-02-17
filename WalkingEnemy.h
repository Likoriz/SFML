#pragma once
#include "Entity.h"
class WalkingEnemy : public Entity
{
private:
	int health;
	bool isDead;
public:
	WalkingEnemy(MyDrawable* object);
	//void update(std::chrono::duration<double> time_span, std::chrono::steady_clock::time_point& last_time, std::chrono::steady_clock::time_point current_time);
	void follow();
	void leave();
	void attack();
	void destruct();
	void triggerMove(GameObject* target);
	void sendMessage(Message m);
	void checkCollision(std::chrono::duration<double> time_span, std::chrono::steady_clock::time_point& last_time, std::chrono::steady_clock::time_point current_time);
};

