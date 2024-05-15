#include "PlatformDisappearing.h"

using namespace sf;

PlatformDisappearing::PlatformDisappearing(MyDrawable* object)
{
	setDrawable(object);
	Rect<int> rect = object->getRect();
	Vector2i tileSize = Manager::getInstance()->getLevel()->getTileSize();
	if (getDrawable()->getName() == "sliding")
		setObject(new Object(b2_staticBody, rect.left + tileSize.x / 2 * (rect.width / tileSize.x - 1), rect.top + tileSize.y / 2 * (rect.height / tileSize.y - 1), rect));
	else
		setObject(new Object(b2_staticBody, rect.left + tileSize.x / 2 * (rect.width / tileSize.x - 1), rect.top + tileSize.y / 2 * (rect.height / tileSize.y - 1) - tileSize.y, rect));
}

void PlatformDisappearing::sendMessage(Message m)
{

}

void PlatformDisappearing::checkCollision(std::chrono::duration<double> time_span, std::chrono::steady_clock::time_point& last_time, std::chrono::steady_clock::time_point current_time)
{

}