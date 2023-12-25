#pragma once
#include <iostream>

class Medal
{
private:
	bool isCollected;
	std::string name;
	float lastTimeTriggered;
public:
	virtual void causeEffect() = 0;
	bool getCollected();
	void setCollected(bool state);
	void setName(std::string name_);
	std::string getName();
};

