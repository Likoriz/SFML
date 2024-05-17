#include "GameObject.h"
class PlatformUsual : public GameObject
{
public:
	PlatformUsual(MyDrawable* object);
	void sendMessage(Message m);
};