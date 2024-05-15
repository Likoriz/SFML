#include "Medal6.h"
#include "Player.h"

using namespace std;

Medal6::Medal6()
{
	setName("Two Ends");
	setCollected(true);
}

void Medal6::causeEffect()
{
	Player* p = dynamic_cast<Player*>(Manager::getInstance()->getByName("player"));

    b2Body* body = p->getObject()->getBody();

    b2Vec2 center = body->GetPosition();
    b2Body* currentBody = Manager::getInstance()->getWorld()->GetBodyList();
    int r = p->getRadius();

    while (currentBody) 
    {
        if (currentBody != body && currentBody->GetType() == b2_dynamicBody) 
        { 
            b2Vec2 bodyPosition = currentBody->GetPosition();
            float distance = (bodyPosition - center).Length();

            if (distance <= r) 
            {
                b2Vec2 v = currentBody->GetLinearVelocity();
                v.x = body->GetLinearVelocity().x;
                currentBody->SetLinearVelocity(v);
            }
        }
        currentBody = currentBody->GetNext();
    }
}