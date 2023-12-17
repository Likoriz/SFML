#include "Medal.h"
using namespace std;

Medal::Medal()
{
	isCollected = false;
}

bool Medal::getCollected()
{
	return isCollected;
}

void Medal::setCollected(bool state)
{
	isCollected = state;
}

void Medal::setName(string name_)
{
	name = name_;
}

string Medal::getName()
{
	return name;
}