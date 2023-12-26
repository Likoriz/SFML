#include "HidingEnemy.h"

using namespace std;
using namespace std::chrono;

HidingEnemy::HidingEnemy()
{
	setHP(50);
	setDMG(20);
	setDEF(50);
}

void HidingEnemy::sendMessage(Message m)
{

}

void HidingEnemy::attack()
{
}

void HidingEnemy::hide()
{
}

void HidingEnemy::show()
{
}

void HidingEnemy::destruct()
{
}

void HidingEnemy::checkCollision(duration<double> time_span, steady_clock::time_point& last_time, steady_clock::time_point current_time)
{
	vector<GameObject*> deathObjects = Manager::getInstance()->getVectorByName("death");

	Message m;
	for (b2ContactEdge* edge = getObject()->getBody()->GetContactList(); edge; edge = edge->next)
	{
		b2Contact* contact = edge->contact;

		for (auto x : deathObjects)
			if (contact->GetFixtureA() == x->getObject()->getBody()->GetFixtureList() || contact->GetFixtureB() == x->getObject()->getBody()->GetFixtureList())
			{
				last_time = current_time;
				Message m;
				m.type = DealDmg;
				m.target = this;
				m.ctx.dealDmg.dmg = this->getHP();
				Manager::getInstance()->SendMessage(m);
				break;
			}
	}
}