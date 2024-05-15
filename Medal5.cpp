#include "Medal5.h"
#include "Player.h"

Medal5::Medal5()
{
	setName("Passive Income");
	setCollected(true);
}

void Medal5::causeEffect()
{
	Player* p = dynamic_cast<Player*>(Manager::getInstance()->getByName("player"));
	p->setCoins(p->getCoins() + 1);
}
