#include "GameObject.h"
class Box : public GameObject
{
public:
	Box(MyDrawable* object);
	void sendMessage(Message m);
};