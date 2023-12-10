#pragma once
enum class MessageType {Move,Death,Render,RenderAll,Create,DealDmg,TriggerEffect, Erase};
#include "GameObject.h"
#include <vector>
class MyDrawable;


struct Message
{
	MessageType type;
	GameObject* sender;
	union
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
			MyDrawable* targetToRender;
		} render;
		struct
		{
			std::vector<MyDrawable*> everyone;
		} renderAll;
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
		} create;
	};
};