#include "GameObject.h"
class PlatformUsual : public GameObject
{
public:
	void sendMessage(Message m);
	void move() {}
};