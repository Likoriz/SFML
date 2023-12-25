#include "Skills.h"

Skills::Skills()
{
	isAbleToClimb = false;
	isAbleToDoubleJump = false;
	isAbleToTripleJump = false;
	isAbleToDash = false;
	isAbleToWallJump = false;
}

void Skills::setSkill()
{
	//switch (skill)
	//{
	//case CLIMB:
	//	isAbleToClimb = true;
	//	break;
	//case DOUBLE:
	//	isAbleToDoubleJump = true;
	//	break;
	//case TRIPLE:
	//	isAbleToTripleJump = true;
	//	break;
	//case DASH:
	//	isAbleToDash = true;
	//	break;
	//case WALL:
	//	isAbleToWallJump = true;
	//	break;
	//}
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
	else if (!isAbleToWallJump)
	{
		isAbleToWallJump = true;
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
	case WALL:
		return isAbleToWallJump;
	default:
		return false;
	}
}