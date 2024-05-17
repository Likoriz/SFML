#include "GameObject.h"

class PlatformSliding : public GameObject
{
public:
	PlatformSliding(MyDrawable* object);
	void sendMessage(Message m);
};