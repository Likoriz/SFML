#pragma once
class Medal
{
private:
	bool isCollected;
public:
	Medal();
	virtual void causeEffect() = 0;
};

