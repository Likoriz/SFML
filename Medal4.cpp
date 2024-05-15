#include "Medal4.h"
#include "Player.h"

Medal4::Medal4()
{
	setName("Boost DMG");
	setCollected(true);
	setTriggered(false);
}

void Medal4::causeEffect()
{
	if (getTriggered() == false)
	{
		Player* p = dynamic_cast<Player*>(Manager::getInstance()->getByName("player"));
		p->setDMG(p->getDMG() + 50);
		setTriggered(true);
	}
}
