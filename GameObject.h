#pragma once
#include "Object.h"
#include "MyDrawable.h"
#include "Manager.h"
class Message;

#include <vector>
class GameObject
{
private:
	MyDrawable* drawable;
	Object* object;
public:
	void setDrawable(MyDrawable* object);
	MyDrawable* getDrawable();
	void setObject(Object* sourceObject);
	Object* getObject();
	/*virtual void Update(float dt) = 0;*/
	//virtual void SendMessage(Message m) = 0;
	GameObject();
	GameObject(const GameObject&);
	~GameObject();
};

