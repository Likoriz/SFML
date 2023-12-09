#pragma once
#include "Object.h"
#include "MyDrawable.h"
#include <vector>
class GameObject
{
private:
	std::vector<MyDrawable> drawables;
	std::vector<Object> objects;
public:
	MyDrawable** GetDrawables;
	void addDrawable(MyDrawable object_);
	void addObject(Object object_);
};

