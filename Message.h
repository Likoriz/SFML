#pragma once
enum MessageType {Move,Death,Render,Create,DealDmg,TriggerEffect, Erase};
class GameObject;
#include <vector>
class MyDrawable;


struct Message
{
	MessageType type;
	GameObject* sender;
	union triggeredMessage
	{
		struct
		{
			int xOld, yOld;
		} move;
		struct
		{
			GameObject* target;
			GameObject* killer;
		} death;
		struct
		{
			GameObject* newObject;
		} create;
		struct
		{
			float dmg;
			GameObject* target;
			GameObject* dealer;
		} dealDmg;
		struct
		{
			GameObject* target;
		} triggerEffect;
		struct
		{
			GameObject* objectToDelete;
		} destroy;
	}ctx;
};