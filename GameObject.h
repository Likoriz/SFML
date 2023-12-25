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
	void move();
	void setDrawable(MyDrawable* object);
	MyDrawable* getDrawable();
	bool getIsOnGround();
	void setIsOnGround(bool flag);
	void setObject(Object* sourceObject);
	Object* getObject();
	void update();
	virtual void sendMessage(Message m)=0;
	GameObject();
	GameObject(const GameObject&);
	~GameObject();
	
};

