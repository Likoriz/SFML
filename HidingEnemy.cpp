#include "HidingEnemy.h"

using namespace std;
using namespace std::chrono;
using namespace sf;

HidingEnemy::HidingEnemy(MyDrawable* object)
{
	setHP(50);
	setDMG(20);
	setDEF(50);
	health=50;
	isDead=false;
	setDrawable(object);
	Rect<int> rect=object->getRect();
	Vector2i tileSize=Manager::getInstance()->getLevel()->getTileSize();
	setObject(new Object(b2_dynamicBody, rect.left+tileSize.x/2*(rect.width/tileSize.x-1), rect.top+tileSize.y/2*(rect.height/tileSize.y-1), rect, true));
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

void HidingEnemy::attack(Message m)
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