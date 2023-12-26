#include "WalkingEnemy.h"

using namespace std;
using namespace std::chrono;

WalkingEnemy::WalkingEnemy()
{
	setHP(50);
	setDMG(20);
	setDEF(50);
	health=50;
	isDead=false;
}

void WalkingEnemy::follow()
{
}

void WalkingEnemy::leave()
{
}

void WalkingEnemy::attack()
{
}

void WalkingEnemy::destruct()
{
}


void WalkingEnemy::sendMessage(Message m)
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

void WalkingEnemy::checkCollision(duration<double> time_span, steady_clock::time_point& last_time, steady_clock::time_point current_time)
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

