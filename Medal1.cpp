#include "Medal1.h"
#include "Manager.h"

Medal1::Medal1()
{
	setName("Regeneration");
	setCollected(false);
}

void Medal1::causeEffect()//regeneration
{
	//if(getLastTimeTicks()%5000)
	Message heal;
	heal.type=DealDmg;
	heal.ctx.dealDmg.target=Manager::getInstance()->getByName("player");
	heal.ctx.dealDmg.dmg=5;
	Manager::getInstance()->SendMessage(heal);
}
