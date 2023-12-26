#include "Box.h"
using namespace sf;
Box::Box(MyDrawable* object)
{
	setDrawable(object);
	Rect<int> rect=object->getRect();
	Vector2i tileSize=Manager::getInstance()->getLevel()->getTileSize();
	setObject(new Object(b2_dynamicBody, rect.left+tileSize.x/2*(rect.width/tileSize.x-1), rect.top+tileSize.y/2*(rect.height/tileSize.y-1), rect, true));
}

void Box::sendMessage(Message m)
{

}
