#include "Skills.h"

Skills::Skills()
{
	isAbleToClimb = false;
	isAbleToDoubleJump = false;
	isAbleToTripleJump = false;
	isAbleToDash = false;
	isAbleToWallJump = false;
}

void Skills::setSkill(int skill)
{
	switch (skill)
	{
	case CLIMB:
		isAbleToClimb = true;
		break;
	case DOUBLE:
		isAbleToDoubleJump = true;
		break;
	case TRIPLE:
		isAbleToTripleJump = true;
		break;
	case DASH:
		isAbleToDash = true;
		break;
	case WALL:
		isAbleToWallJump = true;
		break;
	}
}