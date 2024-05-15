#include "PlatformSliding.h"

using namespace sf;

PlatformSliding::PlatformSliding(MyDrawable* object)
{
	setDrawable(object);
	Rect<int> rect = object->getRect();
	Vector2i tileSize = Manager::getInstance()->getLevel()->getTileSize();
	setObject(new Object(b2_staticBody, rect.left + tileSize.x / 2 * (rect.width / tileSize.x - 1), rect.top + tileSize.y / 2 * (rect.height / tileSize.y - 1) - tileSize.y, rect, true, 1.0, 0.1));
}

void PlatformSliding::sendMessage(Message m)
{

}

void PlatformSliding::checkCollision(std::chrono::duration<double> time_span, std::chrono::steady_clock::time_point& last_time, std::chrono::steady_clock::time_point current_time)
{

}