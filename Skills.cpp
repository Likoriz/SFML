#include "Skills.h"
#include <box2d\box2d.h>

Skills::Skills()
{
	isAbleToClimb = false;
	isAbleToDoubleJump = true;
	isAbleToTripleJump = false;
	isAbleToDash = false;
}

void Skills::setSkill()
{
	if (!isAbleToDoubleJump)
	{
		isAbleToDoubleJump = true;
		return;
	}
	else if (!isAbleToTripleJump)
	{
		isAbleToTripleJump = true;
		return;
	}
	else if (!isAbleToDash)
	{
		isAbleToDash = true;
		return;
	}
	else if (!isAbleToClimb)
	{
		isAbleToClimb = true;
		return;
	}
}

bool Skills::getSkill(int number)
{
	switch (number)
	{
	case CLIMB:
		return isAbleToClimb;
	case DOUBLE:
		return isAbleToDoubleJump;
	case TRIPLE:
		return isAbleToTripleJump;
	case DASH:
		return isAbleToDash;
	default:
		return false;
	}
}