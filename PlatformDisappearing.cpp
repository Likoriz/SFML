#include "PlatformDisappearing.h"

using namespace sf;

PlatformDisappearing::PlatformDisappearing(MyDrawable* object)
{
	isShown = true;
	setDrawable(object);
	Rect<int> rect = object->getRect();
	Vector2i tileSize = Manager::getInstance()->getLevel()->getTileSize();
	setObject(new Object(b2_staticBody, rect.left + tileSize.x / 2 * (rect.width / tileSize.x - 1), rect.top + tileSize.y / 2 * (rect.height / tileSize.y - 1) - tileSize.y, rect));
}

void PlatformDisappearing::sendMessage(Message m)
{

}

void PlatformDisappearing::update(std::chrono::duration<double> time_span, std::chrono::steady_clock::time_point& last_time, std::chrono::steady_clock::time_point current_time)
{
	if (time_span.count() > 5)
	{
		if (isShown)
			disappear();
		else
			show();
	}
}

void PlatformDisappearing::show()
{
	getObject()->getBody()->SetEnabled(true);
	isShown = true;
}

void PlatformDisappearing::disappear()
{
	getObject()->getBody()->SetEnabled(false);
	isShown = false;
}

bool PlatformDisappearing::getIsShown()
{
	return isShown;
}