#pragma once
class Medal
{
private:
	bool medals[8];
public:
	virtual void causeEffect() = 0;
	void showMenu();
};

