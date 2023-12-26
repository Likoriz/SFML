#include "HidingEnemy.h"

using namespace std;
using namespace std::chrono;

HidingEnemy::HidingEnemy()
{
	setHP(50);
	setDMG(20);
	setDEF(50);
	health=50;
	isDead=false;
}

void HidingEnemy::sendMessage(Message m)
{
	if(!isDead)
	{
		switch(m.type)
		{
		case Move:
		{
			b2Body* enemyBody=getObject()->getBody();

			b2Vec2 speed;
			speed={m.ctx.move.speedX, m.ctx.move.speedY};

			enemyBody->SetLinearVelocity(speed);
			break;
		}
		case DealDmg:
		{
			health-=m.ctx.dealDmg.dmg;
			if(health>getHP())
				health=getHP();
			else if(health<1)
			{
				isDead=true;
				Message M;
				M.type=Erase;
				M.ctx.erase.objectToDelete=this;
				Manager::getInstance()->SendMessage(M);
			}
			break;
		}
		}
	}
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