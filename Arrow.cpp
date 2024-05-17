#include "Arrow.h"

using namespace std::chrono;
using namespace sf;

Arrow::Arrow(MyDrawable* object)
{
	setDrawable(object);
	Rect<int> rect=object->getRect();
	Vector2i tileSize=Manager::getInstance()->getLevel()->getTileSize();
	setObject(new Object(b2_dynamicBody, rect.left, rect.top-tileSize.y, rect, true, 1.0, 1.0));
}

void Arrow::attack(Message m)
{
}

void Arrow::destruct()
{
}

void Arrow::sendMessage(Message m)
{
}

void Arrow::checkCollision(duration<double> time_span, steady_clock::time_point& last_time, steady_clock::time_point current_time)
{

}