#pragma once
class Skills
{
private:
	enum Skill { CLIMB = 0, DOUBLE, TRIPLE, DASH};
	bool isAbleToClimb;
	bool isAbleToDoubleJump;
	bool isAbleToTripleJump;
	bool isAbleToDash;
public:
	Skills();
	void setSkill();
	bool getSkill(int number);
};

