#include "GameObject.h"

class PlatformFalling : public GameObject
{
private:
	bool isFalling;
	float originalYPos;
	float dy;
	std::chrono::steady_clock::time_point lastTimeMoved = std::chrono::steady_clock::now();
public:
	PlatformFalling(MyDrawable* object);
	void sendMessage(Message m);
	void update(std::chrono::duration<double> time_span, std::chrono::steady_clock::time_point& last_time, std::chrono::steady_clock::time_point current_time);
	void fall();
	void getUp();
};