#include "Medal3.h"
#include "Manager.h"
#include "Player.h"

Medal3::Medal3()
{
	setName("Boost HP");
	setCollected(true);
	setTriggered(false);
}

void Medal3::causeEffect()
{
	if (getTriggered() == false)
	{
		Player* p = dynamic_cast<Player*>(Manager::getInstance()->getByName("player"));
		p->setHP(p->getHP() + 50);
		setTriggered(true);
	}
}
