#include "WalkingEnemy.h"

using namespace std;
using namespace std::chrono;
using namespace sf;

WalkingEnemy::WalkingEnemy(MyDrawable* object)
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

void WalkingEnemy::update(std::chrono::duration<double> time_span, std::chrono::steady_clock::time_point& last_time, std::chrono::steady_clock::time_point current_time)
{
	if(getObject()->getBody()->GetLinearVelocity().x==0&&getObject()->getBody()->GetLinearVelocity().y==0)
		triggerMove(this);
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

void WalkingEnemy::triggerMove(GameObject* target)
{
	Message M;
	if(rand()%2)
		M.ctx.move.speedX=-45.0f;
	else
		M.ctx.move.speedX=45.0f;
	M.type=Move;
	M.target=target;
	M.ctx.move.speedY=target->getObject()->getBody()->GetLinearVelocity().y;
	Manager::getInstance()->SendMessage(M);
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

