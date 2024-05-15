#include "Medal2.h"
#include "Player.h"

Medal2::Medal2()
{
	setName("Invincibility");
	setCollected(true);
}

void Medal2::causeEffect()
{
	Player* p = dynamic_cast<Player*>(Manager::getInstance()->getByName("player"));
	p->setInvicibility(!(p->getInvincibility()));
}
