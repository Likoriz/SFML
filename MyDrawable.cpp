#include "MyDrawable.h"
using namespace std;
using namespace sf;

int MyDrawable::getPropertyInt(string name)
{
	return 0;
}

float MyDrawable::getPropertyFloat(string name)
{
	return 0;
}

string MyDrawable::getPropertyString(string name)
{
	return "a";
}

void MyDrawable::setName(string name_)
{
	name=name_;
}

void MyDrawable::setType(string type_)
{
	type=type_;
}

void MyDrawable::setSprite(Sprite sprite_)
{
	sprite=sprite_;
}

void MyDrawable::setRect(Rect<int> rect_)
{
	rect.top = rect_.top;
	rect.left=rect_.left;
	rect.height=rect_.height;
	rect.width=rect_.width;
}

void MyDrawable::setProperties(std::map<std::string, std::string> properties_)
{
	copy(properties.begin(), properties.end(), inserter(properties_, properties_.begin()));
}