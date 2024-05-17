#include "PlatformFalling.h"
#include "GameObject.h"

using namespace sf;
using namespace std;
using namespace std::chrono;

PlatformFalling::PlatformFalling(MyDrawable* object)
{
	isFalling = false;
	dy = 36.0f;
	setDrawable(object);
	Rect<int> rect = object->getRect();
	Vector2i tileSize = Manager::getInstance()->getLevel()->getTileSize();
	setObject(new Object(b2_staticBody, rect.left + tileSize.x / 2 * (rect.width / tileSize.x - 1), rect.top + tileSize.y / 2 * (rect.height / tileSize.y - 1) - tileSize.y, rect));
	originalYPos = getObject()->getBody()->GetPosition().y;
}

void PlatformFalling::sendMessage(Message m)
{

}

void PlatformFalling::update(std::chrono::duration<double> time_span, std::chrono::steady_clock::time_point& last_time, std::chrono::steady_clock::time_point current_time)
{
	GameObject* player = Manager::getInstance()->getByName("player");

	Message m;
	b2ContactEdge* edge;
	for (edge = getObject()->getBody()->GetContactList(); edge; edge = edge->next)
	{
		b2Contact* contact = edge->contact;

		if (contact->GetFixtureA() == getObject()->getBody()->GetFixtureList() || contact->GetFixtureB() == getObject()->getBody()->GetFixtureList())
			if (!contact->GetFixtureA()->IsSensor() && !contact->GetFixtureB()->IsSensor())
				if (player->getDrawable()->getName() == "player")
				{
					isFalling = true;
					fall();
				}
	}

	if (!edge)
	{
		duration<double> dt = duration_cast<duration<double>>(current_time - lastTimeMoved);
		if (dt.count() > 5)
			getUp();
	}
}

void PlatformFalling::fall()
{
	if (isFalling)
	{
		float currentYPos = getObject()->getBody()->GetPosition().y;
		b2Vec2 newPosition = getObject()->getBody()->GetPosition();
		if (abs(newPosition.y - originalYPos) < dy)
		{
			if (originalYPos > currentYPos)
				newPosition.y = currentYPos - 1;
			else
				newPosition.y = currentYPos + 1;

			getObject()->getBody()->SetTransform(newPosition, 0);
			move();
			lastTimeMoved = steady_clock::now();
		}
	}
	else
		getUp();
}

void PlatformFalling::getUp()
{
	float currentYPos = getObject()->getBody()->GetPosition().y;
	b2Vec2 newPosition = getObject()->getBody()->GetPosition();

	if (currentYPos != originalYPos)
	{
		if (originalYPos > currentYPos)
			newPosition.y = currentYPos + 1;
		else
			newPosition.y = currentYPos - 1;

		getObject()->getBody()->SetTransform(newPosition, 0);
		move();
	}
}