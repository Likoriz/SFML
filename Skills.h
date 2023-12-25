#pragma once
class Skills
{
private:
	enum Skill { CLIMB = 0, DOUBLE, TRIPLE, DASH, WALL };
	bool isAbleToClimb;
	bool isAbleToDoubleJump;
	bool isAbleToTripleJump;
	bool isAbleToDash;
	bool isAbleToWallJump;
public:
	Skills();
	void setSkill();
	bool getSkill(int number);
};

