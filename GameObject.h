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
	void move();
	void setDrawable(MyDrawable* object);
	MyDrawable* getDrawable();
	void setObject(Object* sourceObject);
	Object* getObject();
	virtual void update(std::chrono::duration<double> time_span, std::chrono::steady_clock::time_point& last_time, std::chrono::steady_clock::time_point current_time);
	virtual void sendMessage(Message m)=0;
	GameObject();
	GameObject(const GameObject&);
	~GameObject();
};

