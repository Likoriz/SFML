#pragma once
#include "Object.h"
#include "Drawable.h"
class GameObject
{
private:
	Drawable** drawables;
	Object** objects;
public:
	Drawable** GetDrawables;
};

