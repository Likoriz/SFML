#pragma once
#include "Object.h"
#include "MyDrawable.h"
#include "Message.h"
#include <vector>
class GameObject
{
private:
	MyDrawable* drawable;
	Object* object;
public:
	void setDrawable(MyDrawable* object);
	virtual void Update(float dt) = 0;
	virtual void SendMessage(Message m) = 0;
	//void addDrawable(MyDrawable* object_);
	//void addObject(Object* object_);
};

