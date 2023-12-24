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
	bool isOnGround;
public:
	virtual void move() = 0;
	void setDrawable(MyDrawable* object);
	MyDrawable* getDrawable();
	bool getIsOnGround();
	void setObject(Object* sourceObject);
	Object* getObject();
	/*virtual void Update(float dt) = 0;*/
	virtual void sendMessage(Message m)=0;
	GameObject();
	GameObject(const GameObject&);
	~GameObject();
	
};

