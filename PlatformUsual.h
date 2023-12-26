#include "GameObject.h"
class PlatformUsual : public GameObject
{
public:
	PlatformUsual(MyDrawable* object);
	void sendMessage(Message m);
	void move() {};
	void checkCollision(std::chrono::duration<double> time_span, std::chrono::steady_clock::time_point& last_time, std::chrono::steady_clock::time_point current_time);
};