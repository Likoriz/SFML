#pragma once
enum MessageType {Move,Death,Render,Create,DealDmg,Erase};
class GameObject;
#include <vector>
class MyDrawable;
#include "box2d/box2d.h"

struct Message
{
	MessageType type;
	GameObject* target;
	union triggeredMessage
	{
		struct
		{
			float speedX,speedY;
		} move;
		struct
		{
			GameObject* killer;
		} death;
		struct
		{
			GameObject* newObject;
		} create;
		struct
		{
			float dmg;
			GameObject* dealer;
		} dealDmg;
		struct
		{
			GameObject* objectToDelete;
		} destroy;
	}ctx;
};