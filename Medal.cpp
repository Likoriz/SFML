#include "Medal.h"

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