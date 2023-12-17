#pragma once
#include "Object.h"
#include "MyDrawable.h"
class Message;

#include <vector>
class GameObject
{
private:
	MyDrawable* drawable;
	Object* object;
public:
	void setDrawable(MyDrawable* object);
	void setObject(Object* sourceObject);
	/*virtual void Update(float dt) = 0;
	virtual void SendMessage(Message m) = 0;*/
	GameObject();
	GameObject(const GameObject&);
	~GameObject();
	//void addDrawable(MyDrawable* object_);
	//void addObject(Object* object_);
};

