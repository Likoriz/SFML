#include "GameObject.h"

class PlatformDisappearing : public GameObject
{
private:
	bool isShown;
public:
	PlatformDisappearing(MyDrawable* object);
	void sendMessage(Message m);
	void update(std::chrono::duration<double> time_span, std::chrono::steady_clock::time_point& last_time, std::chrono::steady_clock::time_point current_time);
	void show();
	void disappear();
	bool getIsShown();
};